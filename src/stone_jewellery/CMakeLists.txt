cmake_minimum_required(VERSION 3.2)
project(stone_jewellery)

set(compile_definitions )
if(WIN32)
    list(APPEND compile_definitions
        _UNICODE
        UNICODE)
endif()

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -municode")
endif()

add_executable(stone_jewellery
    "src/main.cpp")

target_compile_definitions(stone_jewellery
    PRIVATE
    ${compile_definitions})

target_link_libraries(stone_jewellery
    PRIVATE
    Yatest::coverage
    Yatest::stone_jewellery_lib)
