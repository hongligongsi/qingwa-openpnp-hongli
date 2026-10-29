"""Serve the standalone tool on loopback; no third-party dependencies."""
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import os

if __name__ == '__main__':
    os.chdir(Path(__file__).resolve().parent)
    print('OpenPnP hardware tool: http://localhost:8765 (Ctrl+C to stop)')
    ThreadingHTTPServer(('127.0.0.1', 8765), SimpleHTTPRequestHandler).serve_forever()
