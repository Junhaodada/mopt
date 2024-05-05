#ifndef MOPT_L1MIN_H
#define MOPT_L1MIN_H

#include "types.h"

class l1min {
public:
    l1min() {}

    ~l1min() {}

    l1min(float64 mu, float64 cCoef, int64 cNorm, int64 cExp, const Matrix &A, const Vector &b, int64 m, int64 n);

    // l1_min solve
    void solve(string alog_type);

    // model base paramters
    float64 mu;
    int8 x_norm;
    float64 c_coef;
    int64 c_norm;
    int64 c_exp;
    Matrix A;
    Vector b;
    int64 m;    // A's row
    int64 n;    // A's column
    // x
    Vector x;
};

#endif // MOPT_L1MIN_H