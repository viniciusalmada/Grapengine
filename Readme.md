# Grapengine
A 3D Graphics Engine made with C++ and OpenGL core profile.

### Build

This project use `CMakelists` and `VCPKG` as package manager.

To configure you must have the path for vcpkg _toolchain_ (`${VCPKG_TOOLCHAIN}`).

```shell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="${VCPKG_TOOLCHAIN}"
```