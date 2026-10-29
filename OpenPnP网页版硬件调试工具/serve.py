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
from urllib.parse import quote
import os

# 入口页面文件名（中文名，不再是服务器默认自动打开的 index.html）
ENTRY_PAGE = '硬件调试台.html'


class Handler(SimpleHTTPRequestHandler):
    """自定义请求处理：把根路径 / 和旧路径 /index.html 都重定向到中文入口页"""

    def send_head(self):
        if self.path in ('/', '/index.html'):
            # 302 临时重定向到 URL 编码后的中文文件名
            self.send_response(302)
            self.send_header('Location', '/' + quote(ENTRY_PAGE))
            self.end_headers()
            return None
        return super().send_head()


# 切换工作目录到脚本所在目录，确保能找到 硬件调试台.html / app.js / core.js 等静态资源
if __name__ == '__main__':
    os.chdir(Path(__file__).resolve().parent)
    print('青蛙硬件调试台: http://localhost:8765 (Ctrl+C to stop)')
    ThreadingHTTPServer(('127.0.0.1', 8765), Handler).serve_forever()
