@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by MYFIRSTMFC.HPJ. >"hlp\myfirstMFC.hm"
echo. >>"hlp\myfirstMFC.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\myfirstMFC.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\myfirstMFC.hm"
echo. >>"hlp\myfirstMFC.hm"
echo // Prompts (IDP_*) >>"hlp\myfirstMFC.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\myfirstMFC.hm"
echo. >>"hlp\myfirstMFC.hm"
echo // Resources (IDR_*) >>"hlp\myfirstMFC.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\myfirstMFC.hm"
echo. >>"hlp\myfirstMFC.hm"
echo // Dialogs (IDD_*) >>"hlp\myfirstMFC.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\myfirstMFC.hm"
echo. >>"hlp\myfirstMFC.hm"
echo // Frame Controls (IDW_*) >>"hlp\myfirstMFC.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\myfirstMFC.hm"
REM -- Make help for Project MYFIRSTMFC


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\myfirstMFC.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\myfirstMFC.hlp" goto :Error
if not exist "hlp\myfirstMFC.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\myfirstMFC.hlp" Debug
if exist Debug\nul copy "hlp\myfirstMFC.cnt" Debug
if exist Release\nul copy "hlp\myfirstMFC.hlp" Release
if exist Release\nul copy "hlp\myfirstMFC.cnt" Release
echo.
goto :done

:Error
echo hlp\myfirstMFC.hpj(1) : error: Problem encountered creating help file

:done
echo.
