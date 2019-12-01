cmake_minimum_required(VERSION 3.0)
project(coverage)

set(compile_options )
set(link_options )
set(cxx_libraries )

if(YATEST_COVERAGE)
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        list(APPEND compile_options "-O0" "-fprofile-arcs" "-ftest-coverage")
        list(APPEND link_options "--coverage")
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

add_library(coverage INTERFACE)

add_library(Yatest::coverage ALIAS coverage)

target_link_libraries(coverage
    INTERFACE
    ${cxx_libraries}
    "${link_options_linear}")

target_compile_options(coverage
    INTERFACE
    ${compile_options})
