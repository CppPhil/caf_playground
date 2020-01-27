add_library(
    cafPlaygroundLibrary 
    STATIC 
    library/file.hpp 
    library/file.cpp
)

target_link_libraries(
    cafPlaygroundLibrary
    PUBLIC
    ${CAF_LIBRARIES}
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

