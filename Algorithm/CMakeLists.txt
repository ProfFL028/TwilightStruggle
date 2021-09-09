cmake_minimum_required(VERSION 3.19)
project(Algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(main tests/BigIntTEst.cpp)

file(GLOB_RECURSE files *.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable(${exe} ${file} dataStructure/entity/GameEntry.cpp dataStructure/entity/Scores.cpp dataStructure/entity/Scores.h dataStructure/entity/IndexOutOfBounds.cpp dataStructure/entity/IndexOutOfBounds.h dataStructure/entity/Board.cpp dataStructure/entity/Board.h)
    message(\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()