cmake_minimum_required(VERSION 3.2)
project(top_test)

add_executable(top_test
    "src/top_test.cpp")

target_link_libraries(top_test
    PRIVATE
    Yatest::coverage
    Yatest::mull
    gtest_main
    Yatest::top_lib)

add_test(NAME top_test COMMAND ${YATEST_CTEST_COMMAND} $<TARGET_FILE:top_test>)
