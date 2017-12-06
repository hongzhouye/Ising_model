#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <cmath>


using namespace std;
typedef vector<int> iv1;
typedef vector<iv1> iv2;
typedef vector<double> dv1;
typedef vector<dv1> dv2;


template <class T>
T sum_matrix(const vector<vector<T>>& S)
{
    T sum = T(0);
    for(int i = 0; i < S.size(); i++)
        for(int j = 0; j < S[i].size(); j++)
            sum += S[i][j];

    return sum;
}


#endif
