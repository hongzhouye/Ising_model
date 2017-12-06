#include "include/utils.hpp"
#include "include/rng.hpp"
#include "include/param.hpp"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: input\n");
        exit(1);
    }

    // initialize random number generator
    init_rng(time(0));

    // read parameters from file
    PARAM p = PARAM(string(argv[1]));

    // run
    p.kernel();

    // average
    p.average();

    // print
    p.print_results();

    return 0;
}
