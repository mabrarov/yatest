cmake_minimum_required(VERSION 3.2)
project(top_solver)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(top_solver STATIC
    "include/top_solver.hpp"
    "src/top_solver.cpp")

add_library(Yatest::top_solver ALIAS top_solver)

target_compile_features(top_solver
    PRIVATE
    cxx_auto_type
    cxx_range_for)

target_compile_definitions(top_solver
    PUBLIC
    ${compile_definitions})

target_include_directories(top_solver
    PUBLIC
    "include")

target_link_libraries(top_solver
    PRIVATE
    Yatest::coverage)
