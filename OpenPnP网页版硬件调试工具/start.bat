@echo off
REM ============================================================
REM  青蛙硬件调试台 — Windows 一键启动脚本
REM  双击运行后会自动打开 localhost:8765 的网页
REM  （实际访问时请用 Chrome / Edge）
REM ============================================================

REM 切换到脚本所在目录
cd /d "%~dp0"

REM 打印访问提示
echo Open http://localhost:8765 in Chrome or Edge.

REM 启动 Python HTTP 服务器（serve.py 不依赖第三方包）
python serve.py

REM 暂停，方便查看报错信息
pause
