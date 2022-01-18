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

install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)


enable_testing()

# does the application run
add_test(NAME Runs COMMAND Tutorial 25)

# does the usage message work?
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
  )

# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

# do a bunch of result based tests
do_test(Tutorial 4 "4 is 2")
do_test(Tutorial 9 "9 is 3")
do_test(Tutorial 5 "5 is 2.236")
do_test(Tutorial 7 "7 is 2.645")
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is (-nan|nan|0)")
do_test(Tutorial 0.0001 "0.0001 is 0.01")