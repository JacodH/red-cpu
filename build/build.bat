@echo off
echo Building Red1...

cd ..
gcc -Wall -Wextra -Iinclude src/main.c src/cpu.c src/instructions.c -o build/red1.exe
cd build
echo Done!