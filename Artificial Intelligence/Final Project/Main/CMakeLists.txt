cmake_minimum_required(VERSION 3.22)
project(AI)

set(CMAKE_CXX_STANDARD 11)

add_executable(AI main.cpp main.h
        GLUT.H
        Entity.cpp Entity.h
        State.h
        ChasingState.cpp ChasingState.h
        EscapingState.cpp EscapingState.h
        util.h
        limited_queue.h)