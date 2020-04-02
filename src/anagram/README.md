# Brackets

Checks if 2 strings are [anagrams](https://en.wikipedia.org/wiki/Anagram). 

Conditions

1. First and second lines of input are considered strings to check, both should consist of a-z only
1. Input is taken from standard input stream
1. Output is 1 if input streams are anagrams and 0 otherwise
1. Output is sent to standard output stream
1. Memory consumption should not exceed 20 MB

## Usage

1. Run `anagram` executable and output its exit code

   * Unix / Linux

     ```bash
     echo -e "abcdc\ncdcab" | "${build_dir}/src/anagram/anagram"
     ```

   * Windows, Visual Studio CMake generator

     ```cmd
     (
     echo abcdc
     echo cdcab
     ) | "%build_dir%\src\anagram\%build_type%\anagram.exe"
     ```

   * Windows, NMake / MinGW makefiles CMake generator

     ```cmd
     (
     echo abcdc
     echo cdcab
     ) | "%build_dir%\src\anagram\anagram.exe"
     ```

1. Check output, expected output is

   ```text
   1
   ```
