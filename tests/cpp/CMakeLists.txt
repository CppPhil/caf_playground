add_executable(cafPlaygroundTest test.hpp test.cpp)

target_include_directories(
    cafPlaygroundTest 
    PRIVATE 
    ${cafPlaygroundLibrary_SOURCE_DIR}
)

target_link_libraries(
    cafPlaygroundTest 
    PRIVATE 
    cafPlaygroundLibrary
)

