@echo off
echo Actualizando archivos...
mkdir "%APPDATA%\NGPD" 2>NUL
xcopy /EY "..\..\APPDATA\NGPD" "%APPDATA%\NGPD"
pause