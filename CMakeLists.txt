cmake_minimum_required(VERSION 3.15)
project(radmor)

#standard C++ 14
set(CMAKE_CXX_STANDARD 14)
add_definitions(-std=gnu++0x -DWINVER=0x0500)

#foldery, w których kompilator ma szukać plików nagłówkowych
include_directories(include)

#współdzielone pliki .cpp
set(SOURCE_FILES
        src/Exceptions.cpp
        src/FileImpl.cpp)

add_executable(radmor ${SOURCE_FILES} main.cpp)