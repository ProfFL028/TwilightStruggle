cmake_minimum_required(VERSION 3.19)
project(Algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp dataStructure/Vector.h dataStructure/Vector.cpp)

file(GLOB files dataStructure_tests/*.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable(${exe} ${file})
    message(\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()