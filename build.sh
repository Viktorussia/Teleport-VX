#!/usr/bin/env sh
set -e
. ./VERSION 2>/dev/null || true
echo "Building Teleport VX ${VERSION:-dev}..."
# тут позже добавим реальные шаги сборки
echo "OK"
