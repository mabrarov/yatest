cmake_minimum_required(VERSION 3.0)
project(mull)

set(compile_options )
set(link_options )
set(cxx_libraries )

if(YATEST_MULL)
    if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
        list(APPEND compile_options "-fembed-bitcode" "-g" "-O0")
    endif()
endif()

set(link_options_linear )
set(first_link_option TRUE)
foreach(link_option IN LISTS link_options)
    if(first_link_option)
        set(link_options_linear "${link_option}")
    else()
        set(link_options_linear "${link_options_linear},${link_option}")
    endif()
    set(first_link_option FALSE)
endforeach()

add_library(mull INTERFACE)

add_library(Yatest::mull ALIAS mull)

target_link_libraries(mull
    INTERFACE
    ${cxx_libraries}
    "${link_options_linear}")

target_compile_options(mull
    INTERFACE
    ${compile_options})
