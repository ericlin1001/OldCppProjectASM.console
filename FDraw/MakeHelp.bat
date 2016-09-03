@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by FDRAW.HPJ. >"hlp\FDraw.hm"
echo. >>"hlp\FDraw.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\FDraw.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\FDraw.hm"
echo. >>"hlp\FDraw.hm"
echo // Prompts (IDP_*) >>"hlp\FDraw.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\FDraw.hm"
echo. >>"hlp\FDraw.hm"
echo // Resources (IDR_*) >>"hlp\FDraw.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\FDraw.hm"
echo. >>"hlp\FDraw.hm"
echo // Dialogs (IDD_*) >>"hlp\FDraw.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\FDraw.hm"
echo. >>"hlp\FDraw.hm"
echo // Frame Controls (IDW_*) >>"hlp\FDraw.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\FDraw.hm"
REM -- Make help for Project FDRAW


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\FDraw.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\FDraw.hlp" goto :Error
if not exist "hlp\FDraw.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\FDraw.hlp" Debug
if exist Debug\nul copy "hlp\FDraw.cnt" Debug
if exist Release\nul copy "hlp\FDraw.hlp" Release
if exist Release\nul copy "hlp\FDraw.cnt" Release
echo.
goto :done

:Error
echo hlp\FDraw.hpj(1) : error: Problem encountered creating help file

:done
echo.
