cmake_minimum_required(VERSION 3.10)

option(USE_MYMATH "use tutorial provided math functions?" ON)

project(Tutorial VERSION 1.0)

configure_file ("${PROJECT_SOURCE_DIR}/TutorialConfig.h.in" "${PROJECT_BINARY_DIR}/TutorialConfig.h")

if (USE_MYMATH) 
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
  # list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
endif ()

add_executable(Tutorial tutorial.cpp)
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})
# target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}" ${EXTRA_INCLUDES})
target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")
