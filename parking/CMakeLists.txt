cmake_minimum_required(VERSION 3.21)
project(parking_library)

set(CMAKE_CXX_STANDARD 20)

add_library(parking private/parking_impl.cpp
        private/parking_factory.cpp
        private/pay_on_gate_strategy.cpp
        private/pay_on_ticket_machine_strategy.cpp
        private/gate_control_strategy_factory.cpp)

# Tests ------------------------------------------------------------
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Parking_Tests_run tests/parking_impl_test_suite.cpp
        tests/pay_on_gate_strategy_test_suite.cpp
        tests/pay_on_ticket_machine_test_suite.cpp)
target_link_libraries(Parking_Tests_run parking gates gtest gtest_main gmock gmock_main)