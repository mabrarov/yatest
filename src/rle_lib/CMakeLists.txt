cmake_minimum_required(VERSION 3.2)
project(rle_lib)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(rle_lib STATIC
    "include/rle_lib.hpp"
    "src/rle_lib.cpp")

add_library(Yatest::rle_lib ALIAS rle_lib)

target_compile_features(rle_lib
    PRIVATE
    cxx_auto_type
    cxx_range_for)

target_compile_definitions(rle_lib
    PUBLIC
    ${compile_definitions})

target_include_directories(rle_lib
    PUBLIC
    "include")

target_link_libraries(rle_lib
    PRIVATE
    Yatest::coverage)
