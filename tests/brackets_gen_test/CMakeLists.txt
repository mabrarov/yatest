cmake_minimum_required(VERSION 3.2)
project(brackets_gen_test)

add_executable(brackets_gen_test
    "src/brackets_gen_test.cpp")

target_compile_features(brackets_gen_test PRIVATE cxx_lambdas)

target_link_libraries(brackets_gen_test
    PRIVATE
    Yatest::coverage
    Yatest::mull
    gtest_main
    gmock
    Yatest::brackets_gen_lib)

add_test(NAME brackets_gen_test COMMAND brackets_gen_test)
