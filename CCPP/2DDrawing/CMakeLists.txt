cmake_minimum_required(VERSION 3.24)
project(2DDrawing)

set(CMAKE_CXX_STANDARD 17)

file(GLOB files "${PROJECT_SOURCE_DIR}/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exeFile ${file})
    string(REPLACE "/" "_" exeName ${exeFile})
    add_executable(
            ${exeName}
            "${exeFile}.cpp"
    )
endforeach ()

