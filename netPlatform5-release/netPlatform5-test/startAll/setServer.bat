@echo off
set /p ip=Server's IP:
cd ./Client
echo %ip%>serverInfo.txt
echo 6789>>serverInfo.txt
echo OK!
pause>nul