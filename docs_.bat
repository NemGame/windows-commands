@echo off
for /f "delims=" %%a in ('powershell.exe -command "& {write-host $([Environment]::GetFolderPath('MyDocuments'))}"') do Set "$Value=%%a"
cd %$Value%