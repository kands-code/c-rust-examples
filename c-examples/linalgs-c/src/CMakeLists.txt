cmake_minimum_required(VERSION 3.21)
project(linalgs C)

set(CMAKE_C_STANDARD 17)

set(SOURCE_FILES linalgs.c linalgs.h)

# add_library(linalgs ${SOURCE_FILES})
add_executable(linalgs main.c ${SOURCE_FILES})
