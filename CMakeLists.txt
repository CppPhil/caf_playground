cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cafPlayground)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/cpp)
add_subdirectory(tests/cpp)

