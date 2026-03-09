# To compile:

```bash
Remove-Item -Recurse -Force .\build-mingw

cmake -S . -B build-mingw -G Ninja `
  -DCMAKE_MAKE_PROGRAM="C:\Users\ritwi\scoop\shims\ninja.exe" `
  -DCMAKE_TOOLCHAIN_FILE="C:\Mods\QUACKITY\templates\zenzense-api-starter\vcpkg\scripts\buildsystems\vcpkg.cmake" `
  -DVCPKG_TARGET_TRIPLET=x64-mingw-static

cmake --build build-mingw
```