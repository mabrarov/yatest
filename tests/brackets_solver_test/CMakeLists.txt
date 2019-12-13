cmake_minimum_required(VERSION 3.2)
project(brackets_solver_test)

add_executable(brackets_solver_test
    "src/brackets_solver_test.cpp")

target_link_libraries(brackets_solver_test
    PRIVATE
    Yatest::coverage
    gtest_main
    Yatest::brackets_solver)

add_test(NAME brackets_solver_test COMMAND brackets_solver_test)
