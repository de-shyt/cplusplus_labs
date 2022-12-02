cmake_minimum_required(VERSION 3.24)
project(lab02_bigint)

set(CMAKE_CXX_STANDARD 14)

include_directories(solution)

add_executable(lab02_bigint
        solution/bigint.inc.cpp
        solution/doctest_main.cpp
        solution/tests.cpp)
