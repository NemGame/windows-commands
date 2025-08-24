@echo off
rustc sizeof/src/main.rs -o sizeof.exe >nul
.\sizeof.exe %*