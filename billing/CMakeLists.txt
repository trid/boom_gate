cmake_minimum_required(VERSION 3.21)
project(gate_library)

set(CMAKE_CXX_STANDARD 20)

add_library(billing private/ticks_based_billing_system.cpp)

# Tests ------------------------------------------------------------
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Billing_Tests_run tests/ticks_based_billing_system_test_suite.cpp)
target_link_libraries(Billing_Tests_run billing gtest gtest_main)