cmake_minimum_required(VERSION 3.2)
project(rle_test)

add_executable(rle_test
    "src/rle_test.cpp")

target_link_libraries(rle_test
    PRIVATE
    Yatest::coverage
    Yatest::mull
    gtest_main
    gmock
    Yatest::rle_lib)

add_test(NAME rle_test COMMAND ${YATEST_CTEST_COMMAND} $<TARGET_FILE:rle_test>)
