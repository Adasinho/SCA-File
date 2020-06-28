cmake_minimum_required(VERSION 3.10)
project(radmor)

#standard C++ 14
#set(CMAKE_CXX_STANDARD 11)
add_definitions(-std=gnu++0x -DWINVER=0x0500)

#foldery, w których kompilator ma szukać plików nagłówkowych
include_directories(include
        googletest/googletest/include
        googletest/googlemock/include)

#współdzielone pliki .cpp
set(SOURCE_FILES
        src/Exceptions.cpp
        src/FileImpl.cpp)

# .cpp files for tests
set(TEST_SOURCES
        tests/MainTest.cpp
        tests/FileImplTests.cpp)

# add Google Test library, compile it from CMakeLists.txt
add_subdirectory(googletest)
link_libraries(gmock)

add_executable(radmor ${SOURCE_FILES} main.cpp)

# configuration for tests
add_executable(radmor_test ${SOURCE_FILES} ${TEST_SOURCES})