cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0)

configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(Tutorial tutorial.cpp)
