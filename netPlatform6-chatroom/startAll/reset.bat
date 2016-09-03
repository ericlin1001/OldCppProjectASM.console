@echo off
copy .\Client\serverInfo-backup.txt .\Client\serverInfo.txt
copy .\Server\userData-backup.txt .\Server\userData.txt
echo ok.
pause>nul