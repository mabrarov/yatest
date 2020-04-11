cmake_minimum_required(VERSION 3.2)
project(top_lib)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(top_lib STATIC
    "include/top_lib.hpp"
    "src/top_lib.cpp")

add_library(Yatest::top_lib ALIAS top_lib)

target_compile_features(top_lib
    PRIVATE
    cxx_auto_type
    cxx_range_for)

target_compile_definitions(top_lib
    PUBLIC
    ${compile_definitions})

target_include_directories(top_lib
    PUBLIC
    "include")

target_link_libraries(top_lib
    PRIVATE
    Yatest::coverage
    Yatest::mull)
