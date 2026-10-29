@echo off
REM ============================================================
REM  Frog Hardware Bench - Windows one-click launcher
REM  Starts local server; open http://localhost:8765 in Chrome/Edge
REM  (Chinese UI lives in serve.py / 硬件调试台.html; cmd.exe cannot
REM   reliably parse UTF-8 Chinese comments, so keep this file ASCII)
REM ============================================================

REM Switch to the folder where this bat lives
cd /d "%~dp0"

echo Open http://localhost:8765 in Chrome or Edge.

REM Start the Python HTTP server (serve.py, stdlib only)
python serve.py

REM Keep window open to show any error message
pause
