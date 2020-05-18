# Brackets Pair Generator

Outputs all possible valid sequences of requested number of pairs of brackets in
lexicographic order, like (3 pairs requested):

```text
((()))
(()())
(())()
()(())
()()()
```

## Usage

1. Run `brackets_gen` executable and output its exit code

   * Unix / Linux

     ```bash
     echo 4 | "${build_dir}/src/brackets_gen/brackets_gen"
     ```

   * Windows, Visual Studio CMake generator

     ```cmd
     echo 4 | "%build_dir%\src\brackets_gen\%build_type%\brackets_gen.exe"
     ```

   * Windows, NMake / MinGW makefiles CMake generator

     ```cmd
     echo 4 | "%build_dir%\src\brackets_gen\brackets_gen.exe"
     ```

1. Check output, expected output is

   ```text
   (((())))
   ((()()))
   ((())())
   ((()))()
   (()(()))
   (()()())
   (()())()
   (())(())
   (())()()
   ()((()))
   ()(()())
   ()(())()
   ()()(())
   ()()()()
   ```
