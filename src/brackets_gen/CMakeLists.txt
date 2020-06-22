cmake_minimum_required(VERSION 3.2)
project(brackets_gen)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -municode")
endif()

add_executable(brackets_gen
    "src/main.cpp")

target_compile_definitions(brackets_gen
    PRIVATE
    ${compile_definitions})

target_link_libraries(brackets_gen
    PRIVATE
    Yatest::coverage
    Yatest::brackets_gen_lib)
