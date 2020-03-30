cmake_minimum_required(VERSION 3.2)
project(anagram)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -municode")
endif()

add_executable(anagram
    "src/main.cpp")

target_compile_features(anagram PRIVATE cxx_lambdas)

target_compile_definitions(anagram
    PRIVATE
    ${compile_definitions})

target_link_libraries(anagram
    PRIVATE
    Yatest::coverage
    Yatest::anagram_lib)
