#include "lrmr/lrmr.h"
#include <iostream>
#include "algo/algo.h"

void lrmr::solve(string algo_type) {
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

lrmr::lrmr(float64 mu, int64 m, int64 n, const Matrix &m1, std::vector<std::pair<int, int>> Omega) : mu(mu), m(m), n(n),
                                                                                                     M(m1),
                                                                                                     Omega(Omega) {
    X = Matrix::Zero(m, n);
}
