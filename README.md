# azza-proj

## Requirements

- CMake 3.16+
- C compiler (GCC/Clang)

## Build

```
cmake -S . -B build
cmake --build build
```

The CMake configuration scans for `COMP*` directories that contain a `main.c` file and creates one executable per directory. Each executable is named after the directory and is placed in `build/<DIR>/`. The entire source folder is copied into that same output directory after build.

## Run

Example for `COMP6047001`:

```
./build/COMP6047001/COMP6047001
```

The program expects `restaurant.csv` in the current working directory. The build step copies `COMP6047001/` into `build/COMP6047001/`, so running from that output folder will find the data file.

## License

MIT License except for data and course files.