cmake_minimum_required(VERSION 3.2)

project(advent-of-code-2020)

set(CMAKE_CXX_STANDARD 17)

include_directories(utils)

add_executable(day02 cpp/day-02/main.cpp utils/utils.cpp)
add_executable(day03 cpp/day-03/main.cpp utils/utils.cpp)
add_executable(day04 cpp/day-04/main.cpp utils/utils.cpp)
add_executable(day05 cpp/day-05/main.cpp utils/utils.cpp)
add_executable(day06 cpp/day-06/main.cpp utils/utils.cpp)
add_executable(day10 cpp/day-10/main.cpp utils/utils.cpp)
