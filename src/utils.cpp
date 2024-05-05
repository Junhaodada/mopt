#include "types.h"
#include "utils.h"
#include <random>
#include <Eigen/Dense>
// some utils for solving

// Sgn for Vector
Vector sgn(const Vector &x) {
    Vector sgn_vec = Vector::Zero(x.size());
    for (int i = 0; i < x.size(); ++i) {
        if (x[i] > 0) {
            sgn_vec[i] = 1;
        } else if (x[i] < 0) {
            sgn_vec[i] = -1;
        } else {
            sgn_vec[i] = 0;
        }
    }
    return sgn_vec;
}

// Soft threshold operator for norm 1 with Vector
Vector shrink(const Vector &x, float64 tau) {
    if (x.squaredNorm() > tau) {
        return x - tau * sgn(x);
    } else {
        return Vector::Zero(x.size());
    }
}

// Soft threshold operator for norm 2 with Vector
Vector shrink2(const Vector &x, float64 tau) {
    Vector s_vec = Vector::Zero(x.size());
    auto x_norm2 = x.squaredNorm();
    if (x_norm2 >= tau) {
        s_vec = (1 - tau / x_norm2) * x;
    }
    return s_vec;
}

// Soft threshold operator for norm nuc with Matrix
Matrix shrink_nuc(const Matrix &X, float64 tau) {
    return X;
//    // 使用 JacobiSVD 进行奇异值分解
//    Eigen::JacobiSVD<Eigen::MatrixXd> svd(X, Eigen::ComputeFullU | Eigen::ComputeFullV);
//
//    // 获取 U, S（奇异值的对角矩阵），V^T（V 的转置）
//    Matrix U = svd.matrixU();
//    Matrix S = svd.singularValues().asDiagonal(); // S 为对角矩阵
//    Matrix Vt = svd.matrixV().transpose();
//
//    Matrix d = Matrix::Zero(X.rows(), X.cols());
//    auto s_value = svd.singularValues();
//    for (int i = 0; i < s_value.size(); ++i) {
//        float64 d_max = abs(s_value(i));
//        if (d_max - tau > 0) {
//            d(i, i) = d_max;
//        }
//    }
//    return U * d * Vt;
}

//  Cn^k
std::vector<int> selectKWithoutReplacement(int n, int k) {
    std::vector<int> numbers;

    // 填充 vector 从 1 到 n
    for (int i = 0; i < n; ++i) {
        numbers.push_back(i);
    }

    // 设置随机数生成器的种子
    std::mt19937 rng(std::random_device{}());

    // 打乱 vector 中的元素
    std::shuffle(numbers.begin(), numbers.end(), rng);

    // 截取 vector 的前 k 个数
    std::vector<int> selectedNumbers;
    selectedNumbers.reserve(k);
    for (int i = 0; i < k; ++i) {
        selectedNumbers.push_back(numbers[i]);
    }

    return selectedNumbers;
}

// get lrmr data
void get_lrmr_data(int64 m, int64 n, Matrix &A, Matrix &M, std::vector<std::pair<int, int>> &Omega) {
    A = Matrix::Random(m, n);
    M = Matrix::Zero(m, n);
    for (int i = 0; i < m; ++i) {
        auto selectA = selectKWithoutReplacement(n, n / 2);
        for (int j = 0; j < selectA.size(); ++j) {
            M(i, selectA[j]) = A(i, selectA[j]);
            Omega.push_back(std::pair<int, int>(i, selectA[j]));
        }
    }
}

// Omega mapping
Matrix P(Matrix M, std::vector<std::pair<int, int>> Omega) {
    Matrix P = Matrix::Zero(M.rows(), M.cols());
    for (auto &v: Omega) {
        P(v.first, v.second) = 1;
    }
    return P;
}
