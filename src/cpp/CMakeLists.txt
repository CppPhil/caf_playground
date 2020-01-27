find_library(CAF_CORE_LIB caf_core)
find_library(CAF_IO_LIB caf_io)
find_library(CAF_OPENSSL_LIB caf_openssl)

set(CAF_LIB_DIR ${cafPlayground_SOURCE_DIR}/external/libcaf/build/lib)

add_library(caf_core_lib STATIC IMPORTED)
set_target_properties(caf_core_lib PROPERTIES IMPORTED_LOCATION ${CAF_LIB_DIR}/libcaf_core.a)

add_library(caf_io_lib STATIC IMPORTED)
set_target_properties(caf_io_lib PROPERTIES IMPORTED_LOCATION ${CAF_LIB_DIR}/libcaf_io.a)

add_library(caf_openssl_lib STATIC IMPORTED)
set_target_properties(caf_openssl_lib PROPERTIES IMPORTED_LOCATION ${CAF_LIB_DIR}/libcaf_openssl.a)

add_library(
    cafPlaygroundLibrary 
    STATIC 
    library/file.hpp 
    library/file.cpp
)

target_link_libraries(
    cafPlaygroundLibrary
    PUBLIC
    caf_core_lib
)

target_link_libraries(
    cafPlaygroundLibrary
    PUBLIC
    caf_io_lib
)

target_link_libraries(
    cafPlaygroundLibrary
    PUBLIC
    caf_openssl_lib
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

