cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

project(DataStructure )

include_directories(include)

set (DS_SRC_FILES "")

file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/src/*.cpp")
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    list(APPEND DS_SRC_FILES "src/${exe}.cpp")
    message(\ \ \ \ --\ ${exe}.cpp\ will\ be\ added\ to\ ${DS_SRC_FILES})
endforeach ()

add_library(DS_LIB ${DS_SRC_FILES})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE files "${PROJECT_SOURCE_DIR}/test/*.cc")
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable(
            ${exe}
            "test/${exe}.cc"
    )

    target_link_libraries(
            ${exe}
            gtest_main
            DS_LIB
    )
    message(\ \ \ \ --\ ${exe}\ will\ be\ compiled)
endforeach ()

#
#include(GoogleTest)
#gtest_discover_tests(LArray_test)
