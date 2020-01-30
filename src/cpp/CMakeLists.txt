find_library(CAF_CORE_LIB caf_core)
find_library(CAF_IO_LIB caf_io)
find_library(CAF_OPENSSL_LIB caf_openssl)

find_package(Threads REQUIRED)

### OBJECT LIBRARY
set(
    LIB_HEADERS
    "library/file.hpp"
    "library/hello_world.hpp"
    "library/mirror.hpp"
    "library/testee.hpp"
    "library/int_types.hpp"
)

set(
    LIB_SOURCES
    "library/file.cpp"
    "library/hello_world.cpp"
    "library/mirror.cpp"
    "library/testee.cpp"
)

add_library(
    cafPlaygroundLibrary 
    OBJECT
    ${LIB_HEADERS}
    ${LIB_SOURCES}
)

target_link_libraries(
    cafPlaygroundLibrary
    PUBLIC
    Threads::Threads
)

target_link_libraries(
    cafPlaygroundLibrary
    PUBLIC
    ${CAF_CORE_LIB}
)

target_link_libraries(
    cafPlaygroundLibrary
    PUBLIC
    ${CAF_IO_LIB}
)

target_link_libraries(
    cafPlaygroundLibrary
    PUBLIC
    ${CAF_OPENSSL_LIB}
)

target_include_directories(
    cafPlaygroundLibrary
    PUBLIC
    ${cafPlayground_SOURCE_DIR}/external/libcaf/libcaf_core
)

target_include_directories(
    cafPlaygroundLibrary
    PUBLIC
    ${cafPlayground_SOURCE_DIR}/external/libcaf/libcaf_io
)

target_include_directories(
    cafPlaygroundLibrary
    PUBLIC
    ${cafPlayground_SOURCE_DIR}/external/libcaf/libcaf_openssl
)

target_include_directories(
    cafPlaygroundLibrary
    PUBLIC
    library
)

target_include_directories(
    cafPlaygroundLibrary
    PUBLIC
    ${cafPlayground_BINARY_DIR}
)

target_include_directories(
    cafPlaygroundLibrary
    PRIVATE
    ${cafPlayground_SOURCE_DIR}/external/philslib/include
)

### APPLICATION
add_executable(
    cafPlaygroundApplication 
    application/main.cpp
)

target_link_libraries(
    cafPlaygroundApplication
    PRIVATE
    cafPlaygroundLibrary
)
