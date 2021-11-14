cmake_minimum_required(VERSION 3.17)
project(HW2 C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES Program.c Utils.c Airport.c AirportManager.c Flight.c Airline.c Date.c)

add_executable(HW2 ${SOURCE_FILES})