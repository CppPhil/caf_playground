set(CAF_ROOT_DIR ${cafPlayground_SOURCE_DIR}/external/libcaf)

include(${cafPlayground_SOURCE_DIR}/external/libcaf/cmake/FindCAF.cmake)

find_package(CAF COMPONENTS core io openssl REQUIRED)

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
    ${CAF_LIBRARIES}
)


target_include_directories(
    cafPlaygroundLibrary
    PUBLIC
    ${CAF_INCLUDE_DIRS}
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

