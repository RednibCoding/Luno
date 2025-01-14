@echo off

REM Check if luno.exe exists in the examples directory and delete it
if exist .\examples\luno.exe (
    echo Deleting existing luno.exe in examples directory...
    del .\examples\luno.exe
)

REM Check if luno.exe exists and delete it
if exist luno.exe (
    echo Deleting existing luno.exe...
    del luno.exe
)

REM Compile the program
REM compile with `-mwindows` to remove the console window
echo Compiling luno.c...
gcc -o luno.exe luno.c -L"deps/win32" -llua54 -lm -lgdi32 -luser32 -lwinmm -O3 -Wall -s -fno-strict-aliasing -fomit-frame-pointer

REM Check if the compilation was successful
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)

echo Compilation successful.

REM Copy the compiled executable to the examples directory
if not exist examples (
    mkdir examples
)

copy luno.exe .\examples\ > nul
if %errorlevel% neq 0 (
    echo Failed to copy luno.exe to ./examples.
    exit /b %errorlevel%
)

echo Successfully copied luno.exe to ./examples.

REM Delete the luno.exe from the root after copying
del luno.exe > nul
if %errorlevel% neq 0 (
    echo Failed to delete luno.exe from root.
    exit /b %errorlevel%
)

echo Successfully cleaned up root directory.
