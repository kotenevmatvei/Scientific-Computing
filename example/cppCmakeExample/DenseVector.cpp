#include "DenseVector.hpp"

#include <iostream>


DenseVector::DenseVector(std::initializer_list<double> init) : data(init) {}

DenseVector DenseVector::operator*(double scale) const {
    DenseVector ret = *this;
    for (auto& x : ret.data)
        x *= scale;
    return ret;
}

void DenseVector::print() const {
    for (auto x : data)
        std::cout << x << ", ";
    std::cout << "\n";
}
