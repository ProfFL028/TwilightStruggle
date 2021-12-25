cmake_minimum_required(VERSION 3.20)
project(TinyTensor)

set(CMAKE_CXX_STANDARD 14)

add_executable(TinyTensor main.cpp autodiff/Operators.h autodiff/Operators.cpp autodiff/ExpressionTree.h autodiff/ExpressionTree.cpp)
