cmake_minimum_required(VERSION 3.29)
project(112EpicDrawingProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(112EpicDrawingProject main.cpp
    drawing/bitmap.cpp
    drawing/bitmap.h
    ID/idgenerator.cpp)

    include_directories(ID drawing objects storage)
