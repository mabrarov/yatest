cmake_minimum_required(VERSION 3.2)
project(anagram_test)

add_executable(anagram_test
    "src/anagram_test.cpp")

target_compile_features(anagram_test PRIVATE cxx_lambdas)

target_link_libraries(anagram_test
    PRIVATE
    Yatest::coverage
    Yatest::mull
    gtest_main
    Yatest::anagram_lib)

add_test(NAME anagram_test COMMAND ${YATEST_CTEST_COMMAND} $<TARGET_FILE:anagram_test>)
