cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS_DEBUG "-g")

project(dsa-c C)

add_subdirectory(collections)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} collections)