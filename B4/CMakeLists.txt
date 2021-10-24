cmake_minimum_required(VERSION 3.20)
project(B4)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "C:\\boost_1_77_0")
set(Boost_INCLUDE_DIRS "C:\\boost_1_77_0")
include_directories(${Boost_INCLUDE_DIRS})

add_executable(B4 DataStruct.hpp DataStruct.cpp main.cpp)
add_executable(B4_test DataStruct.hpp DataStruct.cpp test-main.cpp test-data-struct.cpp)
