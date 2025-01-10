#include <iostream>

#include "structures/CSRMatrix.hpp"
#include "structures/DenseVector.hpp"

int main(int, char **) {
  // Blatt 4

  CSRMatrix A(4, 4, {0, 2, 3, 4, 5}, {0, 3, 1, 0, 2}, {1, 1, 1, 1, 1});
  CSRMatrix B(4, 4, {0, 2, 4, 6, 8}, {0, 1, 0, 1, 2, 3, 2, 3},
              {2, -3, 4, 5, 1, -4, 9, -8});

  std::cout << "A:\n" << A << "\n";
  std::cout << "B:\n" << B << "\n";
  // SpGEMM
  CSRMatrix C = A * B;

  // print matrices
  std::cout << "C:\n" << C << "\n";

  /*
  A:
  (1, 0, 0, 1)
  (0, 1, 0, 0)
  (1, 0, 0, 0)
  (0, 0, 1, 0)
  B:
  (2, -3, 0, 0)
  (4, 5, 0, 0)
  (0, 0, 1, -4)
  (0, 0, 9, -8)
  C:
  (2, -3, 9, -8)
  (4, 5, 0, 0)
  (2, -3, 0, 0)
  (0, 0, 1, -4)
  */

  //Blatt 3

  // DenseVector v{1, 2, 3};
  // DenseVector w({-1, 0, 1});

  // Vector operations:
  // v *= 2;
  // std::cout << "v = " << v << "\n";         // (2, 4, 6)
  // std::cout << "3w = " << 3 * w << "\n";    // (-3, 0, 3)
  // std::cout << "w/2 = " << w / 2 << "\n";   // (-0.5, 0, 0.5)
  // std::cout << "v + w = " << v + w << "\n"; // (1, 4, 7)
  // std::cout << "<v,w> = " << v * w << "\n"; // 4
  // v(2) = 42;
  // std::cout << "modified v = " << v << "\n"; // (2, 4, 42)

  // calls the initializer_list constructor
  //CSRMatrix A({{1, 2}, {3, 4}});
  // 1, 2
  // 3, 4
  //std::cout << "A:\n" << A << "\n";

  //DenseVector u = {-1, 1};
  //std::cout << "u = " << u << "\n";
  //std::cout << "Au = " << A * u << "\n"; // (1, 1)

  // calls the triplet constructor
  //CSRMatrix B(3, 2, {{2, 1, -4}, {0, 0, 2}, {0, 1, 3}});
  // 2 3
  // 0 0
  // 0 -4
  //std::cout << "B:\n" << B << "\n";
 }
