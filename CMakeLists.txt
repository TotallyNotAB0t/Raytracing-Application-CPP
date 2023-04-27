cmake_minimum_required(VERSION 3.25)
project(RTX)

set(CMAKE_CXX_STANDARD 17)

add_executable(RTX main.cpp Vector.cpp Vector.h Point.cpp Point.h)
