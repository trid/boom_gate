cmake_minimum_required(VERSION 3.21)
project(boom_gate_application)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(gates)

add_executable(boom_gate main.cpp)


