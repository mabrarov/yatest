cmake_minimum_required(VERSION 3.2)
project(yatest)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -municode")
endif()

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

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    ${compile_definitions}
)