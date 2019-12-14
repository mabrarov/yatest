cmake_minimum_required(VERSION 3.2)
project(top_solver_test)

add_executable(top_solver_test
    "src/top_solver_test.cpp")

target_link_libraries(top_solver_test
    PRIVATE
    Yatest::coverage
    gtest_main
    Yatest::top_solver)

add_test(NAME top_solver_test COMMAND top_solver_test)
