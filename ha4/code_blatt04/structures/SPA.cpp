#include "SPA.hpp"
#include <tuple>

void SPA::accumulate(double value, size_t pos) {
  if (b.at(pos) == 0) {
    w.at(pos) = value;
    b.at(pos) = 1;
    LS.push_back(pos);
  } else {
    w.at(pos) += value;
  }
};

void SPA::reset() {
  LS.clear();
  w.assign(cols, 0);
  b.assign(cols, 0);
};

std::tuple<size_t, std::vector<double>, std::vector<size_t>>
SPA::output(std::vector<double> val, std::vector<size_t> col) {
  size_t nzi = 0;
  while (!LS.empty()) {
    size_t cptr = LS.front();
    col.push_back(cptr);
    val.push_back(w.at(cptr));
    LS.pop_front();
    nzi++;
  };
  return std::make_tuple(nzi, val, col);
};
