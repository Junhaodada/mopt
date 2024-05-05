#ifndef MOPT_UTILS_H
#define MOPT_UTILS_H

#include "types.h"
#include <vector>

// some utils for solving

// Sgn for Vector
Vector sgn(const Vector &x);

// Soft threshold operator for norm 1 with Vector
Vector shrink(const Vector &x, float64 tau);

// Soft threshold operator for norm 2 with Vector
Vector shrink2(const Vector &x, float64 tau);

// Soft threshold operator for norm nuc with Matrix
Matrix shrink_nuc(const Matrix &X, float64 tau);

void get_lrmr_data(int64 m, int64 n, Matrix &A, Matrix &M, std::vector<std::pair<int, int>> &Omega);

// Omega mapping
Matrix P(Matrix M, std::vector<std::pair<int, int>> Omega);

#endif // MOPT_UTILS_H