@echo off
echo Building Red...

if not exist build mkdir build
gcc -Wall -Wextra -Iinclude src/main.c src/cpu.c src/instructions.c -o build/red1.exe
echo Done!