cmake_minimum_required (VERSION 2.8)

set (CMAKE_CXX_FLAGS "-std=c++17 -pedantic-errors -g")
set (SOURCES src/main.cpp src/state.cpp src/machine.cpp)

add_executable(turing ${SOURCES})
