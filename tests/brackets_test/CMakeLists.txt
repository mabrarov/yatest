cmake_minimum_required(VERSION 3.2)
project(brackets_test)

add_executable(brackets_test
    "src/brackets_test.cpp")

target_link_libraries(brackets_test
    PRIVATE
    Yatest::coverage
    gtest_main
    Yatest::brackets_lib)

add_test(NAME brackets_test COMMAND brackets_test)
