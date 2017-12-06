#include "include/param.hpp"
#include "include/rng.hpp"
#include <cstdio>


PARAM::PARAM(const string& fname)
{
	FILE *p = fopen(fname.c_str(), "r");
	// ignore the first line
	char buffer[100];
	fgets(buffer, 100, p);

	double buf;
	fscanf(p, "%lf", &buf);
	fscanf(p, "\n");
	L = (int) buf;
	fscanf(p, "%lf", &buf);
	fscanf(p, "\n");
	T = buf;
	fscanf(p, "%lf", &buf);
	fscanf(p, "\n");
	H = buf;
	fscanf(p, "%lf", &buf);
	fscanf(p, "\n");
	MaxStep = (long int) buf;
	fscanf(p, "%lf", &buf);
	fscanf(p, "\n");
	AveStep = (long int) buf;
	fscanf(p, "%lf", &buf);
	fscanf(p, "\n");
	int init_lat_type = (int) buf;
	fscanf(p, "%lf", &buf);
	fscanf(p, "\n");
	write_freq = (int) buf;
	fgets(buffer, 100, p);
	int l_buffer = strlen(buffer);
	buffer[l_buffer-1] = '\0';
	outfile = string(buffer);

    S = iv2(L, iv1(L));
	init_lat(S, init_lat_type);

	M_siteave = dv1(MaxStep);
	m_ave = 0.;
	S_ave = dv2(L, dv1(L, 0));
	S2_ave = dv2(L*L, dv1(L*L, 0));
	X_ave = 0.;

	fclose(p);
}


PARAM::PARAM(const int l, const double t, const double h,
    const long int maxstep, long int avestep,
	const int init_lat_type, const int wf, const string& out) :
    L(l), T(t), H(h), MaxStep(maxstep), AveStep(avestep),
	M_siteave(dv1(maxstep)), m_ave(0.), S_ave(dv2(L, dv1(L, 0))),
	S2_ave(dv2(L*L, dv1(L*L, 0))), X_ave(0.), write_freq(wf), outfile(out)
{
    S = iv2(L, iv1(L));
	init_lat(S, init_lat_type);
}


void init_lat(iv2& S, const int init_lat_type)
{
    if (init_lat_type == 1)
        for(int i = 0; i < S.size(); i++)
            for(int j = 0; j < S[i].size(); j++)
                S[i][j] = randi(2) * 2 - 1;
    else
    {
        const int s = (init_lat_type == 2) ? (1) : (-1);
        for(int i = 0; i < S.size(); i++)
            for(int j = 0; j < S[i].size(); j++)
                S[i][j] = s;
    }
}


void PARAM::kernel()
{
	FILE *p = fopen(outfile.c_str(), "w+");
    for(int step = 0; step < MaxStep; step++)
    // big loop over Monte-Carlo step
    {
        // get M_siteave
        M_siteave[step] = sum_matrix(S);

        // generate random sequence for sweeping
        iv1 sweep_order(L*L);
        for(int i = 0; i < L*L; i++)
            sweep_order[i] = randi(L*L);

        // sweep
        for(int sweep = 0; sweep < L*L; sweep++)
        {
            int i = sweep_order[sweep] / L;
            int j = sweep_order[sweep] % L;

            // tentatively flip
            S[i][j] = -S[i][j];

            // calculate energy change of this flip
            double dE = calc_energy_change(S, i, j, L, H);
            //printf("dE = %f\n", dE);

            double Prob = exp(-dE / T);
            double move = randd(0, 1);

            if (move < Prob)    // move!
            {
                //printf("move!\n");
                M_siteave[step] += 2. * S[i][j];
            }
            else                // reject!
            {
                //printf("rej!\n");
                S[i][j] = -S[i][j];
            }
        }

        M_siteave[step] /= float(L * L);

		// write to file
        if (step % write_freq == 0)
            fprintf(p, "%d\t% .5f\n", step, M_siteave[step]);

		// check processing bar
		if (step % (MaxStep / 100) == 0)
			printf("%d\t% .5f\n", step, M_siteave[step]);

		// accumulate m, S and S2 for solving average
		/*if (step >= MaxStep - AveStep)
		{
			m_ave += M_siteave[step];
			for(int i = 0; i < L; i++)
			for(int j = 0; j < L; j++)
			{
				S_ave[i][j] += S[i][j];
				int ij = i * L + j;
				for(int k = 0; k < L; k++)
				for(int l = 0; l < L; l++)
				{
					int kl = k * L + l;
					S2_ave[ij][kl] += S[i][j] * S[k][l];
				}
			}
		}*/
    }

	fclose(p);
}


double calc_energy_change(const iv2& S, const int i, const int j, const int L,
    const double H)
{
    int up = (i == 0) ? (L - 1) : (i - 1);
    int dn = (i + 1) % L;
    int lt = (j == 0) ? (L - 1) : (j - 1);
    int rt = (j + 1) % L;

    int Ssum = S[up][j] + S[dn][j] + S[i][lt] + S[i][rt];

    return 2. * (-Ssum + -H) * S[i][j];
}


void PARAM::average()
// Solve average for M, S2 and S
{
	m_ave /= float(AveStep);
	for(int i = 0; i < L; i++)
	for(int j = 0; j < L; j++)
	{
		S_ave[i][j] /= float(AveStep);
		int ij = i * L + j;
		for(int k = 0; k < L; k++)
		for(int l = 0; l < L; l++)
		{
			int kl = k * L + l;
			S2_ave[ij][kl] /= float(AveStep);
		}
	}

	for(int i = 0; i < L; i++)
	for(int j = 0; j < L; j++)
	{
		int ij = i * L + j;
		for(int k = 0; k < L; k++)
		for(int l = 0; l < L; l++)
		{
			int kl = k * L + l;
			X_ave += S2_ave[ij][kl] - S_ave[i][j] * S_ave[k][l];
		}
	}
	X_ave /= float(L * L);
}


void PARAM::print_results()
{
	printf("m_ave: % .10f\n", m_ave);
	printf("X_ave: % .10f\n", X_ave);
}
