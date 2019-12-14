# Brackets

Checks if input text represents valid sequence of brackets (round, square, curly) only, like:

```text
()[]{}[[()]]{}
```

## Usage

1. Run `brackets` executable and output its exit code

   * Unix / Linux

     ```bash
     echo $("${build_dir}/src/brackets_main/brackets" "()[]{}[[()]]{}")
     ```

   * Windows, Visual Studio CMake generator

     ```cmd
     "%build_dir%\src\brackets_main\%build_type%\brackets.exe" "()[]{}[[()]]{}" ^
     && echo %errorlevel%
     ```

   * Windows, NMake / MinGW makefiles CMake generator

     ```cmd
     "%build_dir%\src\brackets_main\brackets.exe" "()[]{}[[()]]{}" ^
     && echo %errorlevel%
     ```

1. Check output, expected output is

   ```text
   0
   ```
