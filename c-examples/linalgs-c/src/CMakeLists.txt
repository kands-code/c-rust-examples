cmake_minimum_required(VERSION 3.21)
project(linalgs-exe C)

set(CMAKE_C_STANDARD 17)

add_library(linalgs STATIC linalgs.c)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} linalgs)