cmake_minimum_required(VERSION 3.0.0...3.22.0)
project(VectorExample VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(VectorExample main.cpp DenseVector.cpp)
