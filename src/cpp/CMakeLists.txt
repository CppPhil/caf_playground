add_library(
    cafPlaygroundLibrary 
    STATIC 
    library/file.hpp 
    library/file.cpp
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

