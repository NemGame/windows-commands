@echo off
gcc -o lst.exe lst.c -Wl,--subsystem,console -lmingw32 -lshell32
copy lst.exe ../lst.exe >nul
