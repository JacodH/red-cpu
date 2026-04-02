@echo off
echo Building Red...

gcc src/main.c src/cpu.c src/instructions.c src/screen.c -Iinclude -IC:\msys64\mingw64\include -LC:\msys64\mingw64\lib -lSDL2 -o red1.exe
echo Done!