#include "solvers.hpp"
#include "../structures/CSRMatrix.hpp"
#include "../structures/DenseVector.hpp"
#include <iostream>

namespace solvers {
DenseVector conjugateGradient(const CSRMatrix &A, const DenseVector &b,
                              bool verbose, double tolerance) {
  // Blatt 5
  DenseVector xt = DenseVector(b.size(), 1);
  DenseVector rt = b - A * xt;
  DenseVector pt = b - A * xt;
  double alphat = rt * rt;
  size_t t = 0;
  double lambda;
  double alpha_tmp;

  while (alphat >= tolerance) {
    DenseVector vt = A * pt;
    lambda = alphat / (vt * pt);
    xt = xt + lambda * pt;
    rt = rt - lambda * vt;
    alpha_tmp = alphat;
    alphat = rt * rt;
    pt = rt + (alphat / alpha_tmp) * pt;
    if (verbose) {
      std::cout << "Resisdium: " << alphat << "\n";
    }
    ++t;
  }
  if (verbose) {
    std::cout << "Number of iterations: " << t << "\n";
  }
  return pt;
}

} // namespace solvers
