cmake_minimum_required(VERSION 3.19)
project(B4)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "C:\\boost_1_75_0")
set(Boost_INCLUDE_DIRS "C:\\boost_1_75_0")
include_directories(${Boost_INCLUDE_DIRS})

add_executable(B4 main.cpp DataStruct.hpp task.cpp task.hpp)
add_executable(B4_test task.cpp test-main.cpp test-task.cpp task.hpp)