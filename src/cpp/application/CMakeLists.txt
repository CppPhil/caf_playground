cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cafPlaygroundApplication)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE cafPlaygroundLibrary_SOURCE_DIR)

target_link_libraries(${PROJECT_NAME} PRIVATE cafPlaygroundLibrary)

