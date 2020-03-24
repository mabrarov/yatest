# Jewelery & Stones

Counts number of stones which are jewellery.

Conditions

1. First line of input is considered jewellery
1. Second line of input is considered jewellery
1. Each input line should consist of a-z letters only
1. Input is taken from standard input stream
1. Output is the number of stones which are found among jewellery
1. Output is sent to standard output stream

## Usage

1. Run `stone_jewellery` executable and output its exit code

   * Unix / Linux

     ```bash
     echo -e "abcdefg\nxysnbyab" | "${build_dir}/src/stone_jewellery/stone_jewellery"
     ```

   * Windows, Visual Studio CMake generator

     ```cmd
     (
     echo abcdefg
     echo xysnbyab
     ) | "%build_dir%\src\stone_jewellery\%build_type%\stone_jewellery.exe"
     ```

   * Windows, NMake / MinGW makefiles CMake generator

     ```cmd
     (
     echo abcdefg
     echo xysnbyab
     ) |"%build_dir%\src\stone_jewellery\stone_jewellery.exe"
     ```

1. Check output, expected output is

   ```text
   3
   ```
