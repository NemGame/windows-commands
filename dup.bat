@echo off
set "_path=%~1"
set "_name=%~2"

if "%_path%" == "" (
	echo dup path new_path
	exit /b
)

if "%_path:~-1%"=="\" set "_path=%_path:~0,-1%"
for %%A in ("%_path%") do set "_path=%%~fA"

if "%_name%" == "" (
	set "_name=%~1_copy"
)

if exist "%_path%" (
	if exist "%_path%\" (
		robocopy "%_path%" "%_name%" /E /COPY:DAT /R:1 /W:1 >nul
	) else (
		copy "%_path%" "%_name%" >nul
	)
) else (
	echo Nincs ilyen file
)


