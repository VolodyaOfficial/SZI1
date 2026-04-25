cmake_minimum_required(VERSION 3.31)
project(SZI)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(SZI
    src/algorithms.cpp
    src/algorithms.h
    src/io.h
    src/result.h)
