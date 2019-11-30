cmake_minimum_required(VERSION 3.2)
project(solver_test)

add_executable(solver_test
    "src/solver_test.cpp")

target_link_libraries(solver_test
    PRIVATE
    gtest_main
    Yatest::solver)

add_test(NAME solver_test COMMAND solver_test)
