#ifndef DENSE_VECTOR_HPP
#define DENSE_VECTOR_HPP

#include <vector>

class DenseVector
{
private:
    std::vector<double> data;
public:
    DenseVector(std::initializer_list<double> init);
    DenseVector operator*(double scale) const;
    void print() const;
};

#endif
