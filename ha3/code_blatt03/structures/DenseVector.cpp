#include "DenseVector.hpp"


#include <iostream>
#include <vector>

DenseVector::DenseVector(size_t size, double default_value)
    : data(size, default_value)
{
    std::cout << "DenseVector of size " << size 
    << " with default value " << default_value << " constructed\n";
}

DenseVector::DenseVector(std::initializer_list<double> init)
    : data {init}
{
    std::cout << "DensVector with elements ";
    for (const auto& elem : init) {
        std::cout << elem << " ";
    } 
    std::cout << "constructed\n";
}

DenseVector &operator+=(const DenseVector &rhs)
{
    for (size_t ndx = 0; ndx < rhs.size(); ++ndx) 
}