cmake_minimum_required(VERSION 3.9)
project(exceptions)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

add_executable(nesting_test_success nesting_test_success.cpp exceptions.h)
add_executable(nesting_test_failure nesting_test_failure.cpp exceptions.h)

add_executable(destructor_test_success destructor_test_success.cpp exceptions.h)
add_executable(destructor_test_failure destructor_test_failure.cpp exceptions.h)
