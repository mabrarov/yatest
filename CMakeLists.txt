cmake_minimum_required(VERSION 3.2)
project(yatest)

add_executable(${PROJECT_NAME}
    "src/main.cpp")

target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_auto_type
    cxx_nullptr
    cxx_lambdas
    cxx_local_type_template_args
    cxx_range_for
    cxx_rvalue_references)
