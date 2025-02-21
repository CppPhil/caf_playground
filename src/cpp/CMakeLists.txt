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
    "library/typed_calculator.hpp"
    "library/cell.hpp"
    "library/composable_behavior.hpp"
    "library/dictionary.hpp"
    "library/custom_error_handler.hpp"
    "library/delegation.hpp"
    "library/response_promise.hpp"
    "library/aprintf.hpp"
    "library/custom_message_type.hpp"
    "library/ping.hpp"
    "library/pong.hpp"
    "library/hostname.hpp"
    "library/ping_pong_atoms.hpp"
)

set(
    LIB_SOURCES
    "library/file.cpp"
    "library/hello_world.cpp"
    "library/mirror.cpp"
    "library/testee.cpp"
    "library/cell.cpp"
    "library/composable_behavior.cpp"
    "library/dictionary.cpp"
    "library/custom_error_handler.cpp"
    "library/delegation.cpp"
    "library/response_promise.cpp"
    "library/custom_message_type.cpp"
    "library/ping.cpp"
    "library/pong.cpp"
    "library/hostname.cpp"
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
    fmt::fmt
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
    PUBLIC
    ${cafPlayground_SOURCE_DIR}/external/philslib/include
)

target_include_directories(
    cafPlaygroundLibrary
    PUBLIC
    ${cafPlayground_SOURCE_DIR}/external/optional/include
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
