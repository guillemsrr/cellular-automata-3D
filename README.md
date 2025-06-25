# Cellular automata in 3D

![Cellular automata](/screenshots/cellular-automata3.gif)

### Controls

- Click buttons 1,2,3,4 to try different outputs
- R: restart
- UP arrow: increase dimension
- DOWN arrow: decrease dimension

## Build Instructions

This project uses CMake and depends on raylib. Make sure raylib is installed or built locally.
```bash
# Create build directory
mkdir build && cd build

# Generate Visual Studio solution or Makefiles
cmake .. -G "Visual Studio 17 2022" -A x64 -Draylib_DIR="C:/path/to/raylib/build/install/lib/cmake/raylib"

# Build
cmake --build . --config Release
```

### License

This game sources are licensed under an unmodified zlib/libpng license, which is an OSI-certified, BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

*Copyright (c) 2025 Guillem Serra*