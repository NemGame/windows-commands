@echo off
setlocal enabledelayedexpansion

rem === Ha nincs paraméter, kilépünk ===
if "%~1"=="" (
    echo Hasznalat: newfile [fajlnev] [-t "tartalom"]
    exit /b 1
)

if "%~2"=="" (
	type nul > %1
	echo "%1" letrehozva
	exit /b 1
)

echo %2 > %1

echo "%1" letrehozva
echo.
echo Tartalom: %2