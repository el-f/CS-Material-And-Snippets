@echo off

TITLE Select Steam account

taskkill.exe /F /IM steam.exe

cls
echo(
echo(
echo(
echo                                      Select your account
echo                            =======================================
echo(
echo 1) Main (first username)
echo 2) Smurf (second username)
echo 3) Another One (third username)
echo(

CHOICE /M Select /C 123

If Errorlevel 3 Goto 3
If Errorlevel 2 Goto 2
If Errorlevel 1 Goto 1

:3
set username=third username
Goto end
:2
set username=second username
Goto end
:1
set username=first username
Goto end

:end

reg add "HKCU\Software\Valve\Steam" /v AutoLoginUser /t REG_SZ /d %username% /f
reg add "HKCU\Software\Valve\Steam" /v RememberPassword /t REG_DWORD /d 1 /f
start steam://open/main

exit