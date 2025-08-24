@echo off
setlocal enabledelayedexpansion

rem === Ha nincs paraméter, kilépünk ===
if "%~1"=="" (
    echo Usage: newfile [filename] [content]
    exit /b 1
)

if "%~2"=="" (
	type nul > %1
	echo "%1" letrehozva
	exit /b 1
)

echo %2 > %1

echo "%1" created
echo.

echo Content: %2
