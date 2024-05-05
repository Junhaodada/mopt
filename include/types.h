#ifndef MOPT_TYPES_H
#define MOPT_TYPES_H

#include <Eigen/Eigen>
#include <limits>
#include <string>

// base data type
using int8 = int8_t;
using int64 = int64_t;
using float64 = double;
using char32 = char32_t;
using string = std::string;


// matrix data type
using Matrix = Eigen::MatrixXd;
using Vector = Eigen::VectorXd;

#endif  // MOPT_TYPES_H