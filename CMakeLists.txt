cmake_minimum_required(VERSION 3.2)
project(yatest)

option(YATEST_COVERAGE "Add coverage flags for compiler and linker" OFF)

# Turn on grouping of projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Groups of projects reflect location of projects in file system
set(project_group_extern "extern")
set(project_group_src "src")
set(project_group_tests "tests")

# Interface-only target for turning on code coverage
add_subdirectory(cmake/coverage)

add_subdirectory(extern/googletest)
set_target_properties(gtest PROPERTIES FOLDER "${project_group_extern}/gtest")
set_target_properties(gmock PROPERTIES FOLDER "${project_group_extern}/gtest")
set_target_properties(gtest_main PROPERTIES FOLDER "${project_group_extern}/gtest")
set_target_properties(gmock_main PROPERTIES FOLDER "${project_group_extern}/gtest")
target_compile_features(gtest PUBLIC cxx_std_11)
target_compile_features(gmock PUBLIC cxx_std_11)

add_subdirectory(src/codecvt_cast)
add_subdirectory(src/solver)
add_subdirectory(src/main)
set_target_properties(codecvt_cast PROPERTIES FOLDER "${project_group_src}")
set_target_properties(solver PROPERTIES FOLDER "${project_group_src}")
set_target_properties(yatest PROPERTIES FOLDER "${project_group_src}")

enable_testing()
add_subdirectory(tests/solver_test)
set_target_properties(solver_test PROPERTIES FOLDER "${project_group_tests}")
