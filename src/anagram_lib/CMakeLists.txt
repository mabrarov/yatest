cmake_minimum_required(VERSION 3.2)
project(anagram_lib)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(anagram_lib STATIC
    "include/anagram_lib.hpp"
    "src/anagram_lib.cpp")

add_library(Yatest::anagram_lib ALIAS anagram_lib)

target_compile_definitions(anagram_lib
    PUBLIC
    ${compile_definitions})

target_include_directories(anagram_lib
    PUBLIC
    "include")

target_link_libraries(anagram_lib
    PRIVATE
    Yatest::mull
    Yatest::coverage)
