find_library(CAF_CORE_LIB caf_core)
find_library(CAF_IO_LIB caf_io)
find_library(CAF_OPENSSL_LIB caf_openssl)

find_package(Threads REQUIRED)

add_library(
    cafPlaygroundLibrary 
    STATIC 
    library/file.hpp 
    library/file.cpp
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
    ${cafPlayground_SOURCE_DIR}/external/philslib/include
)

add_executable(
    cafPlaygroundApplication 
    application/main.cpp
)

target_include_directories(
    cafPlaygroundApplication
    PRIVATE
    library
)

target_link_libraries(
    cafPlaygroundApplication
    PRIVATE
    cafPlaygroundLibrary
)

