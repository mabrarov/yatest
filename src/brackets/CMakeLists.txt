cmake_minimum_required(VERSION 3.2)
project(brackets)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -municode")
endif()

add_executable(brackets
    "src/main.cpp")

target_compile_features(brackets
    PRIVATE
    cxx_auto_type)

target_compile_definitions(brackets
    PRIVATE
    ${compile_definitions})

target_link_libraries(brackets
    PRIVATE
    Yatest::coverage
    Yatest::codecvt_cast
    Yatest::brackets_lib)
