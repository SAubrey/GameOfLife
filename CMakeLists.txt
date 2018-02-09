cmake_minimum_required(VERSION 3.8)
project(GameOfLife)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c file_utilities.h file_utilities.c)
add_executable(GameOfLife ${SOURCE_FILES})