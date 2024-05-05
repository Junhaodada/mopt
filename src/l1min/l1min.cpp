#include "l1min/l1min.h"
#include <iostream>
#include "algo/algo.h"

void l1min::solve(string algo_type) {
    std::cout << "l1 min solve" << std::endl;
    if (algo_type == "pgm") {
        pgm algo_pgm(5e-4, 1e-4, 2000, 10);
        algo_pgm.execute(this);
    } else if (algo_type == "admm") {
        admm algo_admm(5e-4, 1, 1e-4, 2000, 10);
        algo_admm.execute(this);
    } else {
        std::cout << "Not define algo type: " << algo_type << std::endl;
        return;
    }
}

l1min::l1min(float64 mu, float64 cCoef, int64 cNorm, int64 cExp, const Matrix &A, const Vector &b, int64 m,
             int64 n) : mu(mu), c_coef(cCoef), c_norm(cNorm), c_exp(cExp), A(A), b(b), m(m), n(n) {
    x = Vector::Zero(n);
}