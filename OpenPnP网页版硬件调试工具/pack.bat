@echo off
REM Pack the portable bench tool into a distributable zip.
REM Runs pack.ps1 via PowerShell (bypass policy for this one script).
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0pack.ps1"
pause
