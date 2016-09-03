
echo.>temp.txt
for /f %%i in (%1) do echo order:cmd:(echo %%i^>^>%1) >>temp.txt