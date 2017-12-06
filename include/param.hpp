#ifndef PARAM_HPP
#define PARAM_HPP


#include "utils.hpp"

using namespace std;


class PARAM
{
    public:
        int L;      // lattice dim
        double T;   // reduced temperature
        double H;   // external field
        long int MaxStep;   // max Monte-Carlo step
		long int AveStep;
        iv2 S;      // lattice

        dv1 M_siteave;   // site averaged magnetization (length: MaxStep)

        double m_ave;   // ensemble averaged magnetization
        dv2 S_ave, S2_ave;  // ensemble averaged S and S*S
        double X_ave;

        int write_freq;
        string outfile;

        PARAM() = default;
		PARAM(const string& fname);
        PARAM(const int l, const double t, const double h,
            const long int maxstep, long int avestep,
        	const int init_lat_type, const int wf, const string& out);

        void kernel();
        void average();
        void print_results();
};

void init_lat(iv2& S, const int init_lat_type);
double calc_energy_change(const iv2& S, const int i, const int j, const int L,
    const double H);

#endif
