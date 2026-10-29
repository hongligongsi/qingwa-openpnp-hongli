@echo off
REM ============================================================
REM  Frog Hardware Bench - Windows one-click launcher
REM  Portable: uses bundled Python in runtime\python (no install
REM  needed); falls back to system Python if bundle is missing.
REM  Browser opens http://localhost:8765 automatically.
REM  (ASCII only: cmd.exe cannot reliably parse UTF-8 CJK comments)
REM ============================================================

cd /d "%~dp0"

REM Prefer bundled portable Python, fall back to system python
set "PYEXE=%~dp0runtime\python\python.exe"
if not exist "%PYEXE%" set "PYEXE=python"

echo Open http://localhost:8765 in Chrome or Edge.

"%PYEXE%" serve.py

REM Keep window open to show any error message
pause
