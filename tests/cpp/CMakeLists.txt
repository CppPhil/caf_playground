cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cafPlaygroundTests)

set(TEST_NAME "Unittest")

add_executable(${TEST_NAME} test.hpp test.cpp)

target_include_directories(${TEST_NAME} PRIVATE cafPlaygroundLibrary_SOURCE_DIR)

target_link_libraries(${TEST_NAME} PRIVATE cafPlaygroundLibrary)

