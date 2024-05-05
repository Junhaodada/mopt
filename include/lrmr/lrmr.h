#ifndef MOPT_LRMR_H
#define MOPT_LRMR_H

#include "types.h"

class lrmr {
public:

    void solve(string algo_type);

    lrmr(float64 mu, int64 m, int64 n, const Matrix &m1, std::vector<std::pair<int, int>> Omega);

    float64 mu;
    int64 m;    // M's row
    int64 n;    // M's column

    std::vector<std::pair<int, int>> Omega;
    Matrix M;
    Matrix X;

};

#endif //MOPT_LRMR_H