cmake_minimum_required(VERSION 3.19)
project(B1)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "C:\\boost_1_75_0")
set(Boost_INCLUDE_DIRS "C:\\boost_1_75_0")
include_directories(${Boost_INCLUDE_DIRS})

add_executable(B1 main.cpp access-policies.hpp sort.hpp tasks.cpp tasks.hpp main.cpp utilities.hpp)
add_executable(B1_test access-policies.hpp sort.hpp tasks.cpp tasks.hpp test-main.cpp test-task1.cpp test-task2.cpp test-task3.cpp test-task4.cpp test-main.cpp utilities.hpp)