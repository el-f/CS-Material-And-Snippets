cmake_minimum_required(VERSION 3.17)
project(Lab08 C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main8.c funcs8.c employee.c)

add_executable(Lab8 ${SOURCE_FILES})
