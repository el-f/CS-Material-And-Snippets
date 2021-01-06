cmake_minimum_required(VERSION 3.17)
project(HW3 C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c Airport.c AirportManager.c Company.c Date.c Flight.c General.c listGen.c)

add_executable(HW3 ${SOURCE_FILES})