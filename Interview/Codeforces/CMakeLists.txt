cmake_minimum_required(VERSION 3.19)
project(Codeforces)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        InputGenerator
        "inputGenerator.cpp"
)

file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/Codeforces/(.+)\\..*" "\\1" exeFile ${file})
    string(REPLACE "/" "_" exeName ${exeFile})
    add_executable(
            ${exeName}
            "${exeFile}.cpp"
    )
endforeach ()

