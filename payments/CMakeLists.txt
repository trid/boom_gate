cmake_minimum_required(VERSION 3.21)
project(payments_library)

set(CMAKE_CXX_STANDARD 20)

add_library(payments private/printing_card_payment_provider.cpp
        private/printing_cash_payment_provider.cpp
        private/simple_payment_system.cpp
        private/payment_system_factory.cpp
        private/printing_subscription_payment_provider.cpp)

# Tests ------------------------------------------------------------
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Payments_Tests_run tests/printing_card_payment_provider_test_suite.cpp
        tests/printing_cash_payment_provider.cpp
        tests/simple_payment_system_test_suite.cpp
        tests/printing_subscription_card_payment_provider_test_suite.cpp)
target_link_libraries(Payments_Tests_run payments gtest gtest_main gmock gmock_main)