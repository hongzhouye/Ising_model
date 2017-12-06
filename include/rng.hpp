#ifndef RNG_HPP
#define RNG_HPP


#include <cstdio>
#include <cstdlib>
#include <ctime>


inline void init_rng(const int seed)
{
    srand(seed);
}


inline int randi(const int MAX)
{
    return rand() % MAX;
}


inline double randd(const double min, const double max)
{
    if (max < min)
    {
        printf("In :func:'randd', max must be larger than min.\n");
        exit(1);
    }
    return rand() / float(RAND_MAX) * (max - min) + min;
}

#endif
