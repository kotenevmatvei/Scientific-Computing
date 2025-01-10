#ifndef SPA_HPP
#define SPA_HPP

#include <list>
#include <tuple>
#include <vector>

class SPA {
public:
  const size_t cols;
  std::vector<double> w;
  std::vector<size_t> b;
  std::list<size_t> LS;

  SPA(size_t cols) : cols(cols) {
    w.assign(cols, 0);
    b.assign(cols, 0);
  };

  void accumulate(double value, size_t pos);

  void reset();

  std::tuple<size_t, std::vector<double>, std::vector<size_t>>
  output(std::vector<double> val, std::vector<size_t> col);
};
#endif // SPA_HPP
