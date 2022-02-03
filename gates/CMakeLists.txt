cmake_minimum_required(VERSION 3.21)
project(gate_library)

set(CMAKE_CXX_STANDARD 20)

add_library(gates private/print_gate.cpp)

# Tests ------------------------------------------------------------
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run tests/print_gate_test.cpp)
target_link_libraries(Google_Tests_run gates gtest gtest_main)