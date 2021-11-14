cmake_minimum_required(VERSION 3.17)
project(CFinal C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c q1.c q2.c q3.c GeneralList.c)

add_executable(CFinal ${SOURCE_FILES})
