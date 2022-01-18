cmake_minimum_required(VERSION 3.10)

project(LinearAlgebra VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

list(APPEND EXTRA_LIBS "${PROJECT_SOURCE_DIR}/header")
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/header")

list(APPEND EXTRA_LIBS "${PROJECT_SOURCE_DIR}/src")
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/src")

list(APPEND EXTRA_LIBS "${PROJECT_SOURCE_DIR}/test")
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/test")

enable_testing()

add_executable(
  hello_test
  test/hello_test.cc
  ${EXTRA_LIBS}
)
target_link_libraries(
  hello_test
  gtest_main
  ${EXTRA_LIBS}
)

include(GoogleTest)
gtest_discover_tests(hello_test)

target_include_directories(hello_test PUBLIC "${PROJECT_BINARY_DIR}" ${EXTRA_INCLUDES})
target_include_directories(hello_test PUBLIC "${PROJECT_BINARY_DIR}")
