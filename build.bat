@echo off
IF EXIST "main.exe" (del "main.exe")
gcc -std=c11 -I headers/ source/*.c -o main.exe
