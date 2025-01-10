#ifndef SOLVERS_HPP
#define SOLVERS_HPP

#include "../structures/CSRMatrix.hpp"
#include "../structures/DenseVector.hpp"

namespace solvers {

/// @brief solves the linear system Ax=b up to given tolerance, i.e. until α <
/// tolerance
DenseVector conjugateGradient(const CSRMatrix &A, const DenseVector &b,
                               bool verbose, double tolerance = 1e-6);
} // namespace solvers

#endif
