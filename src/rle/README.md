# RLE

Transforms text consisting of A-Z characters from text like:

```text
AABBBBCCAAARRRTMMMN
```

to text like:

```text
A2B4C2A3R3TM3N
```

## Usage

1. Run `rle` executable and output its exit code

   * Unix / Linux

     ```bash
     "${build_dir}/src/rle/rle" AABBBBCCAAARRRTMMMN
     ```

   * Windows, Visual Studio CMake generator

     ```cmd
     "%build_dir%\src\rle\%build_type%\rle.exe" AABBBBCCAAARRRTMMMN
     ```

   * Windows, NMake / MinGW makefiles CMake generator

     ```cmd
     "%build_dir%\src\rle\rle.exe" AABBBBCCAAARRRTMMMN
     ```

1. Check output, expected output is

   ```text
   AABBBBCCAAARRRTMMMN
   A2B4C2A3R3TM3N
   ```
