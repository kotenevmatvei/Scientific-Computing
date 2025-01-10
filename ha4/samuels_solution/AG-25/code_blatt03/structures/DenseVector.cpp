#include "DenseVector.hpp"

DenseVector::DenseVector(size_t size, double default_value)
  : data(size, default_value) {}

DenseVector::DenseVector(std::initializer_list<double> init)
  : data(init) {}

DenseVector& DenseVector::operator+=(const DenseVector &rhs) {
  for (size_t i = 0; i < this->size(); ++i) {
    data[i] += rhs(i);
  }
  return *this;
}

DenseVector& DenseVector::operator*=(double rhs) {
  for (size_t i = 0; i < this->size(); ++i) {
    data[i] *= rhs;
  }
  return *this;
}

DenseVector& DenseVector::operator/=(double rhs) {
  for (size_t i = 0; i < this->size(); ++i) {
    data[i] /= rhs;
  }
  return *this;
}

double DenseVector::operator*(const DenseVector &rhs) const {
  double result = 0.0;
  for (size_t i = 0; i < this->size(); ++i) {
    result += data[i] * rhs(i);
  }
  return result;
}

double& DenseVector::operator()(size_t idx) {
  return data[idx];
}

double DenseVector::operator()(size_t idx) const {
  return data[idx];
}
