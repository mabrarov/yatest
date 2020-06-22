# C++ Test

[![License](https://img.shields.io/github/license/mabrarov/yatest)](https://github.com/mabrarov/yatest/tree/master/LICENSE)
[![Travis CI build status](https://travis-ci.org/mabrarov/yatest.svg?branch=master)](https://travis-ci.org/mabrarov/yatest)
[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/u5b0i7897pmucqi0/branch/master?svg=true)](https://ci.appveyor.com/project/mabrarov/yatest/branch/master)
[![Code coverage status](https://codecov.io/gh/mabrarov/yatest/branch/master/graph/badge.svg)](https://codecov.io/gh/mabrarov/yatest/branch/master)

C++ tests.

## Building

### Requirements

1. C++ toolchain
   * Microsoft Visual Studio 2015-2019
   * MinGW 7+
   * GCC 6+
   * Clang 6+
1. [CMake](https://cmake.org/) 3.2+

### Assumptions

1. `yatest_home` environment variable is path to local copy of this repository
1. `build_dir` environment variable specifies build directory, 
   it may be different than `yatest_home` for "out of source tree" build, 
   it may be `build` subdirectory of `yatest_home`
1. `build_type` environment variable specifies [CMake build type](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html)
   * `Debug`
   * `Release`
   * `RelWithDebInfo`
   * `MinSizeRel`
1. `cmake_generator` environment variable is [CMake generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)
   * `Visual Studio 14 2015` - Visual Studio 2015
   * `Visual Studio 15 2017` - Visual Studio 2017
   * `Visual Studio 16 2019` - Visual Studio 2019
   * `NMake Makefiles` - NMake makefiles
   * `MinGW Makefiles` - MinGW makefiles
   * `Unix Makefiles` - Unix / Linux makefiles
1. `cmake_platform` environment variable is [CMAKE_GENERATOR_PLATFORM](https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR_PLATFORM.html)
   * `Win32` - x86 platform when using Visual Studio
   * `x64` - amd64 (x64) platform when using Visual Studio
1. Unix / Linux commands use Bash
1. Windows commands use Windows Command Prompt

## Steps

1. Generate project for build system from CMake project, assuming current directory is `build_dir`

   * Unix / Linux

     ```bash
     cmake -D CMAKE_BUILD_TYPE="${build_type}" -G "${cmake_generator}" "${yatest_home}"
     ```

   * Windows, Visual Studio CMake generator, shared C/C++ runtime

     ```cmd
     cmake -G "%cmake_generator%" -A "%cmake_platform%" "%yatest_home%"
     ```

   * Windows, Visual Studio CMake generator, static C/C++ runtime

     ```cmd
     cmake ^
     -D CMAKE_USER_MAKE_RULES_OVERRIDE="%yatest_home%\cmake\static_c_runtime_overrides.cmake" ^
     -D CMAKE_USER_MAKE_RULES_OVERRIDE_CXX="%yatest_home%\cmake\static_cxx_runtime_overrides.cmake" ^
     -G "%cmake_generator%" -A "%cmake_platform%" "%yatest_home%"
     ```

   * Windows, NMake / MinGW makefiles CMake generator, static C/C++ runtime

     ```cmd
     cmake ^
     -D CMAKE_USER_MAKE_RULES_OVERRIDE="%yatest_home%\cmake\static_c_runtime_overrides.cmake" ^
     -D CMAKE_USER_MAKE_RULES_OVERRIDE_CXX="%yatest_home%\cmake\static_cxx_runtime_overrides.cmake" ^
     -D CMAKE_BUILD_TYPE="%build_type%" ^
     -G "%cmake_generator%" "%yatest_home%"
     ```

1. Build generated project with build system chosen at previous step via CMake generator

   * Unix / Linux

     ```bash
     cmake --build "${build_dir}" --config "${build_type}"
     ```

   * Windows

     ```cmd
     cmake --build "%build_dir%" --config "%build_type%"
     ```

1. Run tests, assuming current directory is `build_dir`

   * Unix / Linux

     ```bash
     ctest --build-config "${build_type}" --verbose
     ```

   * Windows

     ```cmd
     ctest --build-config "%build_type%" --verbose
     ```

## Usage

Refer to

1. [src/brackets/README.md](src/brackets/README.md)
1. [src/top/README.md](src/top/README.md)
1. [src/rle/README.md](src/rle/README.md)
1. [src/stone_jewellery/README.md](src/stone_jewellery/README.md)
1. [src/anagram/README.md](src/anagram/README.md)
1. [src/brackets_gen/README.md](src/brackets_gen/README.md)
