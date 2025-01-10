// we had to remove the systems from the directory to make the resulting
// zip size small enough. please add them again before running the code.
#include <chrono>
#include <numeric>
#include <vector>

#include "solvers/solvers.hpp"
#include "structures/CSRMatrix.hpp"
#include "structures/DenseVector.hpp"

void solve_and_calculate_exec_time(const CSRMatrix &A, const DenseVector &a,
                                   size_t N) {
  std::vector<double> times;
  for (size_t i = 0; i < N; ++i) {
    auto start = std::chrono::high_resolution_clock::now();
    const auto x = solvers::conjugateGradient(A, a, false);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    times.push_back(duration.count());
  }
  double mean_duration = std::accumulate(times.begin(), times.end(), 0.0) / N;
  std::cout << "Mean duration for the matrix of dimenstion " << A.cols()
            << " is " << mean_duration << " milliseconds\n";
}

int main(int, char **) {
  const std::string systems_path = "../sparse-systems/";

  const CSRMatrix A(systems_path + "system-01", 100);
  const DenseVector a(systems_path + "system-01");

  const CSRMatrix B(systems_path + "system-02/", 1000);
  const DenseVector b(systems_path + "system-02/");

  const CSRMatrix C(systems_path + "system-03/", 5000);
  const DenseVector c(systems_path + "system-03/");

  const CSRMatrix D(systems_path + "system-04/", 10);
  const DenseVector d(systems_path + "system-04/");

  // we always need 4 iterations

  const auto x = solvers::conjugateGradient(A, a, true);

  std::cout << "CG result for system A: " << x << "\n";

  const auto y = solvers::conjugateGradient(B, b, true);

  std::cout << "CG result for system B: " << y << "\n";

  const auto z = solvers::conjugateGradient(C, c, true);

  std::cout << "CG result for system C: " << z << "\n";

  const auto s = solvers::conjugateGradient(D, d, true);

  std::cout << "CG result for system D: " << s << "\n";

  solve_and_calculate_exec_time(A, a, 10);
  solve_and_calculate_exec_time(B, b, 10);
  solve_and_calculate_exec_time(C, c, 10);
  solve_and_calculate_exec_time(D, d, 10);

  // return 0;
}
