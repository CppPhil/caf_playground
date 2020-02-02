cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

string(APPEND CMAKE_CXX_FLAGS " -Werror -Wall -Wextra -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wpointer-arith -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter -Wlogical-op -Wold-style-cast -Wformat=2 -Wundef -Wduplicated-cond -Wnull-dereference -Wrestrict -Wno-unknown-pragmas")
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -g -O0")
string(APPEND CMAKE_CXX_FLAGS_RELEASE " -O3 -march=native -funroll-loops -flto -fwhole-program -DNDEBUG")

project(cafPlayground VERSION 1.0.0)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

find_package(Git REQUIRED)
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    RESULT_VARIABLE result
    OUTPUT_VARIABLE cafPlayground_GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(result)
    message(FATAL_ERROR "Failed to get git hash: ${result}")
endif()

configure_file(src/cmake/version.hpp.in version.hpp @ONLY)

add_subdirectory(external/fmtlib)
add_subdirectory(external/optional)
add_subdirectory(src/cpp)
add_subdirectory(tests/cpp)

