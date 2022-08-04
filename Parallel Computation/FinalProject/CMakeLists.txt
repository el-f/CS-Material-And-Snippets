cmake_minimum_required(VERSION 3.21)
project(Parallel_Computation C)

set(CMAKE_C_STANDARD 11)

add_executable(
        Parallel_Computation
        src/main.c
        src/utils.c
        src/utils.h
)
