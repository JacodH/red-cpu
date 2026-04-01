@echo off
echo Building Red1...

gcc -Wall -Wextra -Iinclude src/main.c src/cpu.c src/instructions.c -o build/red1.exe
echo Done!