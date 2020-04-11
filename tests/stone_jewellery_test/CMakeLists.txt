cmake_minimum_required(VERSION 3.2)
project(stone_jewellery_test)

add_executable(stone_jewellery_test
    "src/stone_jewellery_test.cpp")

target_link_libraries(stone_jewellery_test
    PRIVATE
    Yatest::coverage
    Yatest::mull
    gtest_main
    Yatest::stone_jewellery_lib)

add_test(NAME stone_jewellery_test COMMAND ${YATEST_CTEST_COMMAND} $<TARGET_FILE:stone_jewellery_test>)
