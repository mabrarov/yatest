cmake_minimum_required(VERSION 3.2)
project(solver)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(solver STATIC
    "include/solver.hpp"
    "src/solver.cpp")

add_library(Yatest::solver ALIAS solver)

target_compile_features(solver
    PRIVATE
    cxx_auto_type
    cxx_range_for)

target_compile_definitions(solver
    PUBLIC
    ${compile_definitions})

target_include_directories(solver
    PUBLIC
    "include")

target_link_libraries(solver
    PRIVATE
    Yatest::coverage)
