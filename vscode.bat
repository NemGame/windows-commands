@echo off
if "%1" == "" (
	code .
	exit /b 1
)
code %*
exit