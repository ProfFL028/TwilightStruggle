
include_directories("../include")

add_library(LA_LIB Linear.cpp)

target_include_directories(LA_LIB INTERFACE $(CMAKE_CURRENT_SOURCE_DIR))