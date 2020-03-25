cmake_minimum_required(VERSION 3.2)
project(codecvt_cast_test)

add_executable(codecvt_cast_test
    "src/codecvt_cast_test.cpp")

target_compile_features(codecvt_cast_test PRIVATE cxx_auto_type)

target_link_libraries(codecvt_cast_test
    PRIVATE
    Yatest::coverage
    gtest_main
    Yatest::codecvt_cast)

add_test(NAME codecvt_cast_test COMMAND codecvt_cast_test)
