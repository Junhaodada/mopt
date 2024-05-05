#include <Eigen/Dense>
#include <iostream>

int main() {
    // 创建一个示例矩阵 m
    Eigen::MatrixXd m(3, 4);
    m << 1, 2, 3, 1,
            4, 5, 6, 1,
            7, 8, 10, 1;

    // 使用 JacobiSVD 进行奇异值分解
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(m, Eigen::ComputeFullU | Eigen::ComputeFullV);

    // 获取 U, S（奇异值的对角矩阵），V^T（V 的转置）
    Eigen::MatrixXd U = svd.matrixU();
    Eigen::MatrixXd S = svd.singularValues().asDiagonal(); // S 为对角矩阵
    Eigen::MatrixXd Vt = svd.matrixV().transpose();

    // 输出 U, S, V^T
    std::cout << "U:\n" << U << std::endl;
    std::cout << "Singular Values:\n" << S << std::endl;
    std::cout << "V^T:\n" << Vt << std::endl;

    return 0;
}