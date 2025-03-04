cmake_minimum_required(VERSION 3.29)
project(test_bitmap)

set(CMAKE_CXX_STANDARD 20)

add_executable(test_bitmap 
	test_bitmap.cpp
        ../bitmap.cpp
	../bitmap.h
)
include_directories(
	..
)
