cmake_minimum_required(VERSION 3.2)
project(codecvt_cast)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(codecvt_cast STATIC
    "include/codecvt_cast.hpp"
    "src/fake.cpp")

add_library(Yatest::codecvt_cast ALIAS codecvt_cast)

target_compile_definitions(codecvt_cast
    PUBLIC
    ${compile_definitions})

target_include_directories(codecvt_cast
    PUBLIC
    "include")
