#include "algo/pgm.h"
#include "utils.h"
#include <iostream>

pgm::pgm(float64 tau, float64 epsilon, int64 maxIter, int64 logInter) : tau(tau), epsilon(epsilon), max_iter(maxIter),
                                                                        log_inter(logInter) {}

void pgm::execute(l1min *problem) {
    std::cout << "pgm for l1min" << std::endl;
    std::cout << "pgm is running for l1min" << std::endl;
    if (problem->c_norm == 2 && problem->c_exp == 1) {
        // problem (1)
        int64 k = 0;
        float64 tau = this->tau;
        float64 epsilon = this->epsilon;
        int64 max_iter = this->max_iter;
        int64 log_inter = this->log_inter;

        Vector lmd = Vector::Zero(problem->m);
        float64 b_norm2 = problem->b.squaredNorm();

        while (true) {
            Vector f_gp = (lmd.transpose() * problem->A).transpose() +
                          problem->A.transpose() * (problem->A * problem->x - problem->b);
            problem->x = shrink(problem->x - tau * f_gp, problem->mu * tau);
            lmd += (problem->A * problem->x - problem->b);  // multipliers
            float64 error = (problem->A * problem->x - problem->b).squaredNorm() / b_norm2;
            if (!(k++ % log_inter)) {
                std::cout << "iter " << k << ",x_norm=" << problem->x.squaredNorm() << ", error=" << error << std::endl;
            }
            if (error < epsilon || k > max_iter) {
                break;
            }
        }
    } else {
        // other problem
    }
    std::cout << "pgm is over for l1min" << std::endl;
}


void pgm::execute(lrmr *problem) {
    std::cout << "pgm for lrmr" << std::endl;
    std::cout << "pgm is running for lrmr" << std::endl;
    int64 k = 0;
    float64 tau = this->tau;
    float64 epsilon = this->epsilon;
    int64 max_iter = this->max_iter;
    int64 log_inter = this->log_inter;

    Matrix lmd = Matrix::Zero(problem->m, problem->n);
    float64 M_norm2 = P(problem->M, problem->Omega).squaredNorm();
    while (true) {
        auto f_gp = P(problem->X - problem->M, problem->Omega);
        auto X_prev = problem->X;
        problem->X = shrink_nuc(problem->X-tau*f_gp, problem->mu*tau);
        lmd = lmd + P(problem->X - problem->M, problem->Omega);
        float64 error1 = P(problem->X - problem->M, problem->Omega).squaredNorm() / M_norm2;
        float64 error2 = (problem->X - X_prev).squaredNorm() / X_prev.squaredNorm();
        if (!(k++ % log_inter)) {
            std::cout << "iter " << k << ",x_norm=" << problem->X.squaredNorm() << ", error1=" << error1 << ", error2="
                      << error2 << std::endl;
        }
        if (error1 < epsilon || error2 < epsilon || k > max_iter) {
            break;
        }
    }
    std::cout << "pgm is over for lrmr" << std::endl;
}

