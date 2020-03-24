cmake_minimum_required(VERSION 3.2)
project(stone_jewellery_test)

add_executable(stone_jewellery_test
    "src/stone_jewellery_test.cpp")

target_link_libraries(stone_jewellery_test
    PRIVATE
    Yatest::coverage
    gtest_main
    Yatest::stone_jewellery_lib)

add_test(NAME stone_jewellery_test COMMAND stone_jewellery_test)
