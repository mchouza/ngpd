@echo off
rem Aparentemente, no tengo COMMON_APPDATA, as� que hay que improvisar:
rem En ingl�s ser�a: set COMMON_APPDATA=%ALLUSERSPROFILE%\Application data\
set COMMON_APPDATA=%ALLUSERSPROFILE%\Datos de programa\
echo Actualizando archivos...
mkdir "%COMMON_APPDATA%\NGPD" 2>NUL
xcopy /EY "..\..\APPDATA\NGPD" "%COMMON_APPDATA%\NGPD"
pause