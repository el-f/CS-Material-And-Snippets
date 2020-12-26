cmake_minimum_required(VERSION 3.17)
project(lab09A C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main09A.c Q.c list.c def.h)

add_executable(lab09A ${SOURCE_FILES})
