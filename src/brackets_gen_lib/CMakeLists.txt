cmake_minimum_required(VERSION 3.2)
project(brackets_gen_lib)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(brackets_gen_lib STATIC
    "include/brackets_gen_lib.hpp"
    "src/brackets_gen_lib.cpp")

add_library(Yatest::brackets_gen_lib ALIAS brackets_gen_lib)

target_compile_definitions(brackets_gen_lib
    PUBLIC
    ${compile_definitions})

target_include_directories(brackets_gen_lib
    PUBLIC
    "include")

target_link_libraries(brackets_gen_lib
    PRIVATE
    Yatest::coverage)
