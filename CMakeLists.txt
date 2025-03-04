cmake_minimum_required(VERSION 3.29)
project(112EpicDrawingProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(112EpicDrawingProject main.cpp
        segment.h
        storage.h
        storage.cpp
        dot.h
        tests.cpp)
