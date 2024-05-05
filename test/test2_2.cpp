#include <iostream>
#include "lrmr/lrmr.h"
#include "utils.h"

int main() {
    std::cout << "lrmr test" << std::endl;

    int64 m = 512;
    int64 n = 1024;
    float64 mu = 10.0;

    Matrix A, M;
    std::vector<std::pair<int, int>> Omega;
    get_lrmr_data(m, n, A, M, Omega);

    lrmr model(mu, m, n, M, Omega);
    model.solve("admm");
}