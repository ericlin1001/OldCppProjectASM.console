@echo off
set conf=Debug
set cp=%~dp0%
set pwd=%cp%..
echo %cp%
set client=Client
set server=Server
copy "%pwd%\%client%\%conf%\%client%.exe" "%cp%\%client%\%client%.exe"
copy "%pwd%\%server%\%conf%\%server%.exe" "%cp%\%server%\%server%.exe"
pause>nul