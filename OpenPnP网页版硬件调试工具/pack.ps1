# -*- coding: utf-8 -*-
# 青蛙硬件调试台 — 便携版打包脚本
# 由 pack.bat 调用（也可手动: powershell -NoProfile -ExecutionPolicy Bypass -File pack.ps1）
# 输出: 项目根目录\青蛙硬件调试台_vX.X_便携版_YYYYMMDD.zip（已在 .gitignore 忽略）

$ErrorActionPreference = 'Stop'
$toolDir = Split-Path -Parent $MyInvocation.MyCommand.Path   # 工具目录
$projRoot = Split-Path -Parent $toolDir                      # 项目根目录

# 从 core.js 头注释里解析版本号（保持与界面显示一致）
$verMatch = Select-String -Path (Join-Path $toolDir 'core.js') -Pattern 'v([\d.]+)' | Select-Object -First 1
$version = if ($verMatch) { $verMatch.Matches[0].Groups[1].Value } else { 'unknown' }
$date = Get-Date -Format 'yyyyMMdd'
$zipName = "青蛙硬件调试台_v${version}_便携版_${date}.zip"
$zipPath = Join-Path $projRoot $zipName

# 用 robocopy 把文件复制到临时目录（排除缓存/日志等无关文件），再压缩
$stage = Join-Path $env:TEMP ("bench_pack_" + [guid]::NewGuid().ToString('N'))
$dest = Join-Path $stage (Split-Path $toolDir -Leaf)   # robocopy 只复制内容，需手动补一层目录名
New-Item -ItemType Directory -Force $dest | Out-Null
$excludeDirs = @('__pycache__', '.git')
$excludeFiles = @('*.pyc', 'pack.ps1', 'pack.bat', 'bench.log')
robocopy $toolDir $dest /E /XD $excludeDirs /XF $excludeFiles /NFL /NDL /NJH /NJS | Out-Null

# 压缩为 zip（顶层带工具目录名，解压后是一个完整文件夹）
if (Test-Path $zipPath) { Remove-Item $zipPath -Force }
Compress-Archive -Path $dest -DestinationPath $zipPath -CompressionLevel Optimal
Remove-Item $stage -Recurse -Force

# 打包结果汇总
$mb = [math]::Round((Get-Item $zipPath).Length / 1MB, 1)
Write-Host ''
Write-Host "打包完成: $zipName" -ForegroundColor Green
Write-Host "位置: $zipPath"
Write-Host "大小: $mb MB"
Write-Host '分发方法: 把 zip 发给对方，解压后双击 start.bat（无需安装 Python）'
