@echo off
if "%~1"=="" (
	powershell -Command "Start-Process -FilePath 'cmd.exe' -ArgumentList '/k cd /d \"%cd%\" & title ye' -Verb RunAs
	exit /b
)
powershell -Command "Start-Process -FilePath 'cmd.exe' -ArgumentList '/k cd /d \"%~1\" & title ye' -Verb RunAs