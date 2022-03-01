cmake_minimum_required(VERSION 3.19)
project(Codeforces)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        InputGenerator
        "inputGenerator.cpp"
)

file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/strings/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    list(APPEND LA_SRC_FILES "src/${exe}.cpp")
    add_executable(
            ${exe}
            "strings/${exe}.cpp"
    )
    message(\ \ \ \ --\ ${exe}.cpp\ will\ be\ added\ to\ ${LA_SRC_FILES})
endforeach ()


file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/bitwise/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    list(APPEND LA_SRC_FILES "src/${exe}.cpp")
    add_executable(
            ${exe}
            "bitwise/${exe}.cpp"
    )
    message(\ \ \ \ --\ ${exe}.cpp\ will\ be\ added\ to\ ${LA_SRC_FILES})
endforeach ()

file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/stateMachine/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    list(APPEND LA_SRC_FILES "src/${exe}.cpp")
    add_executable(
            ${exe}
            "stateMachine/${exe}.cpp"
    )
    message(\ \ \ \ --\ ${exe}.cpp\ will\ be\ added\ to\ ${LA_SRC_FILES})
endforeach ()

file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/sorting/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    list(APPEND LA_SRC_FILES "src/${exe}.cpp")
    add_executable(
            ${exe}
            "sorting/${exe}.cpp"
    )
    message(\ \ \ \ --\ ${exe}.cpp\ will\ be\ added\ to\ ${LA_SRC_FILES})
endforeach ()

file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/array/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    list(APPEND LA_SRC_FILES "src/${exe}.cpp")
    add_executable(
            ${exe}
            "array/${exe}.cpp"
    )
    message(\ \ \ \ --\ ${exe}.cpp\ will\ be\ added\ to\ ${LA_SRC_FILES})
endforeach ()
