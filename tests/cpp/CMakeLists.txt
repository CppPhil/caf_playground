set(
    TEST_SOURCES
    "test.cpp"
    "test2.cpp" 
)

add_executable(
    cafPlaygroundTest 
    "caf-test.cpp"
    "${cafPlayground_SOURCE_DIR}/external/libcaf/libcaf_test/caf/test/unit_test.hpp"
    "${cafPlayground_SOURCE_DIR}/external/libcaf/libcaf_test/caf/test/unit_test_impl.hpp"
    ${TEST_SOURCES}    
)

target_include_directories(
    cafPlaygroundTest
    PRIVATE
    ${cafPlayground_SOURCE_DIR}/external/libcaf/libcaf_test
)

target_link_libraries(
    cafPlaygroundTest 
    PRIVATE 
    cafPlaygroundLibrary
)

