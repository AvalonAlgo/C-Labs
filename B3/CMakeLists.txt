cmake_minimum_required(VERSION 3.19)
project(B3)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_ROOT "C:\\boost_1_77_0")
set(Boost_INCLUDE_DIRS "C:\\boost_1_77_0")
include_directories(${Boost_INCLUDE_DIRS})

add_executable(B3 main.cpp tasks.cpp tasks.hpp phonebook.hpp phonebook.cpp phonebook-interface.hpp phonebook-interface.cpp factorial-container.cpp factorial-container.hpp parser.cpp parser.hpp)
add_executable(B3_test parser.cpp parser.hpp factorial-container.cpp factorial-container.hpp phonebook.hpp phonebook.cpp phonebook-interface.hpp phonebook-interface.cpp test-factorial.cpp test-phonebook-UI.cpp test-main.cpp test-parser.cpp test-phonebook.cpp)