#include "CSRMatrix.hpp"

// Blatt 4

CSRMatrix CSRMatrix::operator*(const CSRMatrix &rhs) const {
    // Empty vectors for IR, JC, and Num
    std::vector<size_t> IR;
    std::vector<size_t> JC;
    std::vector<double> Num;
    
    // Create an empty CSR matrix with the above parameters
    CSRMatrix C(this->n_rows, this->n_cols, IR, JC, Num);

    SPA spa(rhs.n_cols);

    // SpGEMM with CSR
    C.IR.push_back(0);

    for(size_t i = 0; i < this->n_rows; i++) {
        for(size_t k = this->IR[i]; k < this->IR[i + 1]; k++) {
            for(size_t j = rhs.IR[this->JC[k]]; j < rhs.IR[this->JC[k] + 1]; j++) {
                double value = this->Num[k] * rhs.Num[j];
                size_t pos = rhs.JC[j];
                spa.accumulate(value, pos);
            }
        }
        // output spa(spa, C.NUM, C.JC, C.IR(i))
        std::tuple<size_t, std::vector<double>, std::vector<size_t>> output;
        output = spa.output(C.Num, C.JC);
        size_t nzi = std::get<0>(output);
        C.JC = std::get<2>(output);
        C.Num = std::get<1>(output);
        C.IR.push_back(C.IR[i] + nzi);
        spa.reset();
    }
    return C;
};


//Blatt 3

CSRMatrix::CSRMatrix(std::initializer_list<std::initializer_list<double>> init) 
: n_rows(init.size()), n_cols(init.begin()->size()) {
    IR.push_back(0);
    for(size_t i = 0; i < n_rows; i++) {
        for(size_t j = 0; j < n_cols; j++) {
            double a_ij = init.begin()[i].begin()[j];
            if (a_ij != 0.0) {
                Num.push_back(a_ij);
                JC.push_back(j);
            }
        }
        IR.push_back(JC.size());
    }
};

CSRMatrix::CSRMatrix(size_t rows, size_t cols, std::vector<Triplet> triplet_init) 
    : n_rows(rows), n_cols(cols) {
    IR.push_back(0);
    for(size_t k = 0; k < n_rows; k++) {
        for (const auto& triplet : triplet_init) {
            if (triplet.row == k && triplet.value != 0.0) {
                Num.push_back(triplet.value);
                JC.push_back(triplet.col);
            }
        }
        IR.push_back(JC.size());
    }
}


DenseVector CSRMatrix::operator*(const DenseVector &rhs) const {
  DenseVector result(n_rows, 0.0);  // Initialize result vector
  for (size_t i = 0; i < n_rows; ++i) {
    for (size_t idx = IR[i]; idx < IR[i + 1]; ++idx) {
      result(i) += Num[idx] * rhs(JC[idx]);
    }
  }
  return result;
}


double CSRMatrix::operator()(size_t row, size_t col) const {
    for(size_t i = IR[row]; i < IR[row + 1]; i++)
        if (JC[i] == col) {
            return Num[i];
        }
    return 0.0;
}