# -*- coding: utf-8 -*-
"""
青蛙硬件调试台 — 本地 HTTP 服务器启动脚本
------------------------------------------------
- 仅依赖 Python 标准库（http.server），无需 pip 安装任何第三方包
- 默认监听 127.0.0.1:8765，浏览器打开 http://localhost:8765 即可使用
- 关闭终端窗口或 Ctrl+C 停止服务
"""

from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import os

# 切换工作目录到脚本所在目录，确保能找到 index.html / app.js / core.js 等静态资源
if __name__ == '__main__':
    os.chdir(Path(__file__).resolve().parent)
    print('青蛙硬件调试台: http://localhost:8765 (Ctrl+C to stop)')
    ThreadingHTTPServer(('127.0.0.1', 8765), SimpleHTTPRequestHandler).serve_forever()
