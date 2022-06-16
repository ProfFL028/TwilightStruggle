cmake_minimum_required(VERSION 3.21)
project(discoveringModernCPP)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/DiscoveringModernCPP/(.+)\\..*" "\\1" exeFile ${file})
    string(REPLACE "/" "_" exeName ${exeFile})
    add_executable(
            ${exeName}
            "${exeFile}.cpp"
    )
endforeach ()