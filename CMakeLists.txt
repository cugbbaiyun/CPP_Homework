cmake_minimum_required(VERSION 3.19)
project(iris)

set(CMAKE_CXX_STANDARD 20)

add_executable(iris main.cpp consts.h data_utils.cpp data_utils.h Neuron.h Neuron.cpp SGD.h SGD.cpp)