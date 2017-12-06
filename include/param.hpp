#ifndef PARAM_HPP
#define PARAM_HPP


#include "utils.hpp"


class PARAM
{
    public:
        int L;      // lattice dim
        double T;   // reduced temperature
        double H;   // external field
        long int MaxStep;   // max Monte-Carlo step
		long int AveStep;
        iv2 S;      // lattice
        int init_lat_type;  // 1: random; 2: all ones; 3: all minus ones

        dv1 M_siteave;   // site averaged magnetization (length: MaxStep)

        bool iM_ave, iX_ave;
        double m_ave;   // ensemble averaged magnetization
        dv2 S_ave, S2_ave;  // ensemble averaged S and S*S
        double X_ave;

        bool iwrite_traj;
        string write_to;
        int write_freq;

        PARAM() = default;
		PARAM(const string& fname);

        void kernel();
        void average();
        void print_results();
};

void init_lat(iv2& S, const int init_lat_type);
double calc_energy_change(const iv2& S, const int i, const int j, const int L,
    const double H);

#endif
