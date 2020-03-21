cmake_minimum_required(VERSION 3.2)
project(brackets_lib)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(brackets_lib STATIC
    "include/brackets_lib.hpp"
    "src/brackets_lib.cpp")

add_library(Yatest::brackets_lib ALIAS brackets_lib)

target_compile_features(brackets_lib
    PRIVATE
    cxx_auto_type
    cxx_range_for)

target_compile_definitions(brackets_lib
    PUBLIC
    ${compile_definitions})

target_include_directories(brackets_lib
    PUBLIC
    "include")

target_link_libraries(brackets_lib
    PRIVATE
    Yatest::coverage)
