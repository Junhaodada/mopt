#include <iostream>
#include "l1min/l1min.h"

int main() {
    std::cout << "l1 min test1" << std::endl;

    int64 m = 512;
    int64 n = 1024;
    float64 mu = 10.0;
    float64 cCoef = 0.5;
    int64 cNorm = 2;
    int64 cExp = 2;

    const Matrix A = Matrix::Random(m, n);
    const Vector u = Vector::Random(n);
    const Vector b = A * u;

    l1min model(mu, cCoef, cNorm, cExp, A, b, m, n);

    model.solve("admm");
    std::cout << "u_norm=" << u.squaredNorm() << std::endl;
}