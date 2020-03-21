# Top

Finds top N of the most frequent strings among given strings.

Conditions

1. Number of top frequent strings to find (N) is passed as first command line argument
1. Each input line is considered as a separate string to analyze
1. Input is taken from standard input stream
1. Input is read until EOF - use Ctrl+D in Linux and Ctrl+Z in Windows to emulate EOF
1. Top N of the most frequent strings is sent to standard output stream, each string on a new line
1. Output is sorted by frequency in descending order

## Usage

1. Run `top` executable and output its exit code

   * Unix / Linux

     ```bash
     cat <<EOF | "${build_dir}/src/top/top" 2
     a
     a
     a
     a
     a
     b
     b
     c
     c
     c
     EOF
     ```

   * Windows, Visual Studio CMake generator

     ```cmd
     (
     echo a
     echo a
     echo a
     echo a
     echo a
     echo b
     echo b
     echo c
     echo c
     echo c
     ) | "%build_dir%\src\top\%build_type%\top.exe" 2
     ```

   * Windows, NMake / MinGW makefiles CMake generator

     ```cmd
     (
     echo a
     echo a
     echo a
     echo a
     echo a
     echo b
     echo b
     echo c
     echo c
     echo c
     ) | "%build_dir%\src\top\top.exe" 2
     ```

1. Check output, expected output is

   ```text
   a
   c
   ```
