cmake_minimum_required(VERSION 3.17)
project(HW1 C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES Program.c NumberGame.c PictureManipulation.c Utils.c)

add_executable(HW1 ${SOURCE_FILES})