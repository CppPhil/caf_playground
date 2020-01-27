cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cafPlayground)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(CAF_NO_AUTO_LIBCPP TRUE)
set(CAF_NO_OPENCL TRUE)
set(CAF_NO_EXAMPLES TRUE)
set(CAF_NO_UNIT_TESTS TRUE)
set(CAF_NO_PYTHON TRUE)
set(CAF_NO_TOOLS TRUE)
set(CAF_BUILD_STATIC TRUE)
set(CAF_BUILD_STATIC_ONLY TRUE)
add_subdirectory(external/libcaf)

add_subdirectory(src/cpp)
add_subdirectory(tests/cpp)

