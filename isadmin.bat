@echo off
net session >nul 2>&1
if %errorlevel%==0 (
	echo ye
	exit /b
)
echo no
