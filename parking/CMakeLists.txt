cmake_minimum_required(VERSION 3.21)
project(parking_library)

set(CMAKE_CXX_STANDARD 20)

add_library(parking private/parking_impl.cpp)

# Tests ------------------------------------------------------------
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Parking_Tests_run tests/parking_impl_test_suite.cpp)
target_link_libraries(Parking_Tests_run parking gtest gtest_main gmock gmock_main)