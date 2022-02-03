cmake_minimum_required(VERSION 3.21)
project(payments_library)

set(CMAKE_CXX_STANDARD 20)

add_library(payments private/cout_payments.cpp)