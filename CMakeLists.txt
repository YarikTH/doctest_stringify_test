cmake_minimum_required(VERSION 3.14)
project(doctest_stringify_test)

add_subdirectory(libs/doctest)
add_subdirectory(libs/ApprovalTests.cpp)
add_subdirectory(libs/doctest_stl_stringifier)

# Test
add_executable(doctest_stringify_test)

target_sources(doctest_stringify_test PRIVATE main.cpp doctest_to_string_test.cpp)

target_link_libraries(doctest_stringify_test PRIVATE doctest::doctest ApprovalTests::ApprovalTests doctest::stl_stringifier)
