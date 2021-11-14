cmake_minimum_required(VERSION 3.17)
project(Lab09 C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES test.c Person.c listGen.c)

add_executable(Lab9 ${SOURCE_FILES})
