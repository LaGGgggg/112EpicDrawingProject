cmake_minimum_required(VERSION 3.29)
project(112EpicDrawingProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(112EpicDrawingProject main.cpp
    ID/idgenerator.cpp
    ID/idgenerator.h
    drawing/bitmap.cpp
    drawing/bitmap.h
    drawing/test/test_bitmap.cpp
    objects/dot.h
    objects/segment.h
    storage/storage.cpp
    storage/storage.h
    tests/tests.cpp
    tests/tests.h)

    include_directories(ID drawing objects storage tests)
