@echo off
IF EXIST "main.exe" (del "main.exe")
gcc -I headers/ source/*.c -o main.exe
