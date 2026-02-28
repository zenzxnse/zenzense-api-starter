@echo off
setlocal EnableExtensions EnableDelayedExpansion

:: Set local paths
set "PROJECT_DIR=%~dp0"
set "VCPKG_DIR=%PROJECT_DIR%vcpkg"
set "MINGW_DIR=%PROJECT_DIR%mingw"
set "BUILD_DIR=%PROJECT_DIR%build-mingw"
set "MINGW_ARCHIVE=mingw64.7z"
set "MINGW_URL=https://sourceforge.net/projects/mingw-w64/files/Toolchains%%20targetting%%20Win64/Personal%%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download"

:: Git check (SAFE)
git --version >nul 2>&1
if errorlevel 1 (
    echo Error: Git is not installed. Install Git and rerun.
    exit /b 1
)

:: Install local vcpkg if not present
if not exist "%VCPKG_DIR%\vcpkg.exe" (
    echo Installing local vcpkg...
    if not exist "%VCPKG_DIR%" (
        git clone https://github.com/microsoft/vcpkg.git "%VCPKG_DIR%"
    )
    pushd "%VCPKG_DIR%"
    call bootstrap-vcpkg.bat
    popd
)

set "VCPKG_ROOT=%VCPKG_DIR%"

:: Check for system MinGW
set "MINGW_FOUND=0"
g++ --version >nul 2>&1
if not errorlevel 1 set "MINGW_FOUND=1"

if "%MINGW_FOUND%"=="0" (
    if exist "C:\MinGW\bin\g++.exe" (
        set "PATH=C:\MinGW\bin;!PATH!"
        set "MINGW_FOUND=1"
    )
)

:: If no MinGW found, install local one
if "%MINGW_FOUND%"=="0" (
    echo MinGW not found. Installing local MinGW-w64 ^(GCC 8.1.0^) to "!MINGW_DIR!"...
    if not exist "!MINGW_DIR!" mkdir "!MINGW_DIR!"

    echo Downloading MinGW...
    powershell -NoProfile -Command ^
      "$u='%MINGW_URL%'; Invoke-WebRequest -Uri $u -OutFile '%PROJECT_DIR%%MINGW_ARCHIVE%'"

    if exist "%PROJECT_DIR%%MINGW_ARCHIVE%" (
        7z x "%PROJECT_DIR%%MINGW_ARCHIVE%" -o"%MINGW_DIR%" -y
        del "%PROJECT_DIR%%MINGW_ARCHIVE%"

        if exist "%MINGW_DIR%\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64" (
            move "%MINGW_DIR%\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64" "%MINGW_DIR%\mingw64"
            rmdir /s /q "%MINGW_DIR%\x86_64-8.1.0-release-posix-seh-rt_v6-rev0"
        )

        set "PATH=%MINGW_DIR%\mingw64\bin;!PATH!"
    ) else (
        echo Error: Failed to download MinGW.
        exit /b 1
    )
)

echo Installing dependencies with local vcpkg...
"%VCPKG_ROOT%\vcpkg.exe" install --triplet x64-mingw-static

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
pushd "%BUILD_DIR%"

echo Configuring CMake...
cmake .. -G "MinGW Makefiles" ^
  -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" ^
  -DVCPKG_TARGET_TRIPLET=x64-mingw-static

echo Building...
mingw32-make -j%NUMBER_OF_PROCESSORS%

if exist unit_tests.exe (
    echo Running unit tests...
    unit_tests.exe
)

if exist ZENZENSE_API_STARTER.exe (
    echo Build complete. Running the application...
    ZENZENSE_API_STARTER.exe
) else (
    echo Build failed.
)

popd
endlocal
