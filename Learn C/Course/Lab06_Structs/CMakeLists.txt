cmake_minimum_required(VERSION 3.17)
project(Lab6 C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c Address.c Person.c)

add_executable(Lab6 ${SOURCE_FILES})
