cmake_minimum_required(VERSION 3.2)
project(stone_jewellery_lib)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(stone_jewellery_lib STATIC
    "include/stone_jewellery_lib.hpp"
    "src/stone_jewellery_lib.cpp")

add_library(Yatest::stone_jewellery_lib ALIAS stone_jewellery_lib)

target_compile_features(stone_jewellery_lib
    PRIVATE
    cxx_auto_type
    cxx_range_for)

target_compile_definitions(stone_jewellery_lib
    PUBLIC
    ${compile_definitions})

target_include_directories(stone_jewellery_lib
    PUBLIC
    "include")

target_link_libraries(stone_jewellery_lib
    PRIVATE
    Yatest::coverage
    Yatest::mull)
