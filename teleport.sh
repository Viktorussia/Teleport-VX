#!/bin/sh
trap 'printf "\033[?25h\n"; exit' INT TERM EXIT
printf "\033[2J\033[H\033[?25l"
line="========================================"
center="       T E L E П O Р Т   V X"
echo "$line"; echo "$center"; echo "$line"
echo "Viktor Experience • Booting sequence..."
i=0; while [ $i -lt 3 ]; do printf "."; sleep 1; i=$((i+1)); done; echo
echo "Kernel v1.0 — initialized successfully"
sleep 0.5; echo "[ok] CPU: online"
sleep 0.2; echo "[ok] RAM: virtualized"
sleep 0.2; echo "[ok] Input: ready"
for m in fb kbd vfs net time rng; do printf "Loading module: %-6s ... " "$m"; sleep 0.25; echo "ok"; done
echo; echo "Entering userland…"
sleep 0.6; echo "Welcome to Teleport VX core simulation."
printf "\n\033[?25h"
