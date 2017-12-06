#include "include/utils.hpp"
#include "include/rng.hpp"
#include "include/param.hpp"


int main()
{
    // initialize random number generator
    init_rng(time(0));

    // set up parameters in order
    // L, T, H, MaxStep, init_lat_type
    PARAM p("./config.txt");

    // run
    p.kernel();

    // average
    p.average();

    // print
    p.print_results();

    return 0;
}
