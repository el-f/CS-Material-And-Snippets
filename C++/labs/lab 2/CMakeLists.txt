cmake_minimum_required(VERSION 3.21)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES lab2.cpp Survivor.cpp Survivor.h Tribe.cpp Tribe.h)

add_executable(Lab2 ${SOURCE_FILES})