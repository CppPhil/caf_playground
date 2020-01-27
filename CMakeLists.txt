cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cafPlayground)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

find_library(CAF_CORE_LIB caf_core)
find_library(CAF_IO_LIB caf_io)
find_library(CAF_OPENSSL_LIB caf_openssl)

add_subdirectory(src/cpp)
add_subdirectory(tests/cpp)

