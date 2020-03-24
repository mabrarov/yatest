cmake_minimum_required(VERSION 3.2)
project(rle)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -municode")
endif()

add_executable(rle
    "src/main.cpp")

target_compile_features(rle PRIVATE cxx_auto_type)

target_compile_definitions(rle PRIVATE ${compile_definitions})

target_link_libraries(rle
    PRIVATE
    Yatest::coverage
    Yatest::codecvt_cast
    Yatest::rle_lib)
