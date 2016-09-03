@echo off
set app=Server.exe
set happ=hidenRunServer.vbs
cd .\Server
echo createObject("wscript.shell").run "%app%",0 >%happ%
%happ%>nul
del %happ%
echo Server is running in background,you can close this windows...
pause