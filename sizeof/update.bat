@echo off
rustc sizeof/src/main.rs -o sizeof.exe
copy .\sizeof.exe ..\sizeof.exe >nul