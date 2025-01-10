#include "CSRMatrix.hpp"
#include "SPA.cpp"

CSRMatrix CSRMatrix::operator*(const CSRMatrix &rhs) const {
  std::vector<size_t> IR;
  std::vector<size_t> JC;
  std::vector<double> Num;

  CSRMatrix C(this->n_rows, this->n_cols, IR, JC, Num);

  SPA SPA(rhs.n_cols);

  C.IR.push_back(0);

  for (size_t i = 0; i < this->n_rows; i++) {
    for (size_t k = this->IR[i]; k < this->IR[i + 1]; k++) {
      for (size_t j = rhs.IR[this->JC[k]]; j < rhs.IR[this->JC[k] + 1]; j++) {
        double value = this->Num[k] * rhs.Num[j];
        size_t pos = rhs.JC[j];
        SPA.accumulate(value, pos);
      }
    }

    std::tuple<size_t, std::vector<double>, std::vector<size_t>> output;
    output = SPA.output(C.Num, C.JC);
    size_t nzi = std::get<0>(output);
    C.JC = std::get<2>(output);
    C.Num = std::get<1>(output);
    C.IR.push_back(C.IR[i] + nzi);
    SPA.reset();
  }
  return C;
};
