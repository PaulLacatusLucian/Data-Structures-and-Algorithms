cmake_minimum_required(VERSION 3.24)
project(Lab_1_DSA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab_1_DSA
        Set.cpp
        SetIterator.cpp
        ShortTest.cpp
        ExtendedTest.cpp
        app.cpp newIterator.cpp)
