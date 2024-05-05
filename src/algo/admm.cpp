#include <iostream>
#include "algo/admm.h"
#include "utils.h"

admm::admm(float64 tau, float64 gamma, float64 epsilon, int64 maxIter, int64 logInter) : tau(tau), gamma(gamma),
                                                                                         epsilon(epsilon),
                                                                                         max_iter(maxIter),
                                                                                         log_inter(logInter) {}

void admm::execute(l1min *problem) {
    std::cout << "admm for l1min" << std::endl;
    std::cout << "admm is running for l1min" << std::endl;
    if (problem->c_norm == 2 && problem->c_exp == 2) {
        // problem (2)
        int64 k = 0;
        float64 tau = this->tau;
        float64 epsilon = this->epsilon;
        int64 max_iter = this->max_iter;
        int64 log_inter = this->log_inter;

        Vector lmd = Vector::Zero(problem->m);
        Vector y = Vector::Zero(problem->m);

        while (true) {
            Vector f_gp_x = (-lmd.transpose() * problem->A -
                             (y - problem->A * problem->x + problem->b).transpose() * problem->A).transpose();
            auto x_prev = problem->x;
            problem->x = shrink(problem->x - tau * f_gp_x, problem->mu * tau);
            y = 0.5 * (problem->A * problem->x - problem->b - lmd);
            lmd = lmd + gamma * (y - problem->A * problem->x + problem->b);
            float64 error = (problem->x - x_prev).squaredNorm() / x_prev.squaredNorm();
            if (!(k++ % log_inter)) {
                std::cout << "iter " << k << ",x_norm=" << problem->x.squaredNorm() << ", error=" << error << std::endl;
            }
            if (error < epsilon || k > max_iter) {
                break;
            }
        }
    } else if (problem->c_norm == 2 && problem->c_exp == 1) {
        // problem (3)
        int64 k = 0;
        float64 tau_x = this->tau;
        float64 tau_y = this->tau;
        float64 epsilon = this->epsilon;
        int64 max_iter = this->max_iter;
        int64 log_inter = this->log_inter;

        Vector lmd = Vector::Zero(problem->m);
        Vector y = Vector::Zero(problem->m);

        while (true) {
            Vector f_gp_x = (lmd.transpose() * problem->A +
                             (y - problem->A * problem->x + problem->b).transpose() * problem->A).transpose();
            auto x_prev = problem->x;
            problem->x = shrink(problem->x - tau_x * f_gp_x, problem->mu * tau_x);
            Vector f_gp_y = -lmd + (y - problem->A * problem->x + problem->b);
            y = shrink2(y - tau_y * f_gp_y, problem->mu * tau_y);
            lmd = lmd + gamma * (problem->A * problem->x - problem->b - y);
            float64 error = (problem->x - x_prev).squaredNorm() / x_prev.squaredNorm();
            if (!(k++ % log_inter)) {
                std::cout << "iter " << k << ",x_norm=" << problem->x.squaredNorm() << ", error=" << error << std::endl;
            }
            if (error < epsilon || k > max_iter) {
                break;
            }
        }
    } else if (problem->c_norm == 1 && problem->c_exp == 1) {
        // problem (4)
        int64 k = 0;
        float64 tau_x = this->tau;
        float64 tau_y = this->tau;
        float64 epsilon = this->epsilon;
        int64 max_iter = this->max_iter;
        int64 log_inter = this->log_inter;

        Vector lmd = Vector::Zero(problem->m);
        Vector y = Vector::Zero(problem->m);

        while (true) {
            Vector f_gp_x = (lmd.transpose() * problem->A +
                             (y - problem->A * problem->x + problem->b).transpose() * problem->A).transpose();
            auto x_prev = problem->x;
            problem->x = shrink(problem->x - tau_x * f_gp_x, problem->mu * tau_x);
            Vector f_gp_y = -lmd + (y - problem->A * problem->x + problem->b);
            y = shrink(y - tau_y * f_gp_y, problem->mu * tau_y);
            lmd = lmd + gamma * (problem->A * problem->x - problem->b - y);
            float64 error = (problem->x - x_prev).squaredNorm() / x_prev.squaredNorm();
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
    std::cout << "admm is over for l1min" << std::endl;
}

void admm::execute(lrmr *problem) {
    std::cout << "admm for lrmr" << std::endl;
    std::cout << "admm is running for lrmr" << std::endl;
    int64 k = 0;
    float64 tau = this->tau;
    float64 epsilon = this->epsilon;
    int64 max_iter = this->max_iter;
    int64 log_inter = this->log_inter;

    Matrix Y = Matrix::Zero(problem->m, problem->n);
    Matrix lmd = Matrix::Zero(problem->m, problem->n);
    float64 M_norm2 = P(problem->M, problem->Omega).squaredNorm();

    while (true) {
        Matrix f_gp = P(lmd, problem->Omega) + P(problem->X - problem->M - Y, problem->Omega);
        auto X_prev = problem->X;
        problem->X = shrink_nuc(problem->X - tau * f_gp, problem->mu * tau);
        Y = (lmd + P(problem->X - problem->M, problem->Omega)) / 3;
        lmd = lmd + P(problem->X - problem->M, problem->Omega) - Y;
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
    std::cout << "admm is over for lrmr" << std::endl;

}
