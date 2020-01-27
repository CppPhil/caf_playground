cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cafPlaygroundLibrary)

add_library(${PROJECT_NAME} STATIC file.hpp file.cpp)

