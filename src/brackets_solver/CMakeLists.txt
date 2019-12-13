cmake_minimum_required(VERSION 3.2)
project(brackets_solver)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

add_library(brackets_solver STATIC
    "include/brackets_solver.hpp"
    "src/brackets_solver.cpp")

add_library(Yatest::brackets_solver ALIAS brackets_solver)

target_compile_features(brackets_solver
    PRIVATE
    cxx_auto_type
    cxx_range_for)

target_compile_definitions(brackets_solver
    PUBLIC
    ${compile_definitions})

target_include_directories(brackets_solver
    PUBLIC
    "include")

target_link_libraries(brackets_solver
    PRIVATE
    Yatest::coverage)
