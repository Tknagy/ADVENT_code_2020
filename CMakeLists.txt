cmake_minimum_required(VERSION 3.2)

project(advent-of-code-2020)

set(CMAKE_CXX_STANDARD 17)

include_directories(utils)

add_executable(day-02 cpp/day-02/main.cpp utils/utils.cpp)
add_executable(day-03 cpp/day-03/main.cpp utils/utils.cpp)
add_executable(day-04 cpp/day-04/main.cpp utils/utils.cpp)
add_executable(day-05 cpp/day-05/main.cpp utils/utils.cpp)
add_executable(day-06 cpp/day-06/main.cpp utils/utils.cpp)
add_executable(day-10 cpp/day-10/main.cpp utils/utils.cpp)
add_executable(day-11 cpp/day-11/main.cpp utils/utils.cpp)
add_executable(day-12 cpp/day-12/main.cpp utils/utils.cpp)
add_executable(day-14 cpp/day-14/main.cpp utils/utils.cpp)
