#!/usr/bin/env ash

LOGFILE="$HOME/teleport-vx/logs/system.log"

mkdir -p "$HOME/teleport-vx/logs"

log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $*" >> "$LOGFILE"
}
