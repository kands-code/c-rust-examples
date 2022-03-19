cmake_minimum_required(VERSION 3.21)
project(linalgs C)

set(CMAKE_C_STANDARD 17)

set(SOURCE_FILES linear-list/sq-list.c linear-list/sl-list.c)

add_executable(test_c main.c ${SOURCE_FILES})