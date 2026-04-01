@echo off
echo Building Red...

if not exist build mkdir build
gcc src/main.c src/cpu.c src/instructions.c src/screen.c -Iinclude -IC:\msys64\mingw64\include -LC:\msys64\mingw64\lib -lSDL2 -o build/red1.exe
echo Done!