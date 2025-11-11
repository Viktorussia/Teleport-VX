#!/bin/ash
. "$(dirname "$0")/../config/system.cfg"

ansi() { printf "\033[%sm" "$1"; }
ok()   { ansi "1;32"; printf "[OK] %s\n" "$1"; ansi "0"; }
warn() { ansi "1;33"; printf "[WARN] %s\n" "$1"; ansi "0"; }
info() { ansi "1;36"; printf "%s\n" "$1"; ansi "0"; }

kernel_check() { ok "Kernel: active ($KERNEL)"; }

mem_check() {
  if [ -r /proc/meminfo ]; then
    awk '
      BEGIN{t=0;a=0;b=0;c=0}
      /MemTotal:/ {t=$2}
      /MemAvailable:/ {a=$2; haveA=1}
      /MemFree:/ {f=$2}
      /Buffers:/ {b=$2}
      /^Cached:/ {c=$2}
      END{
        if (t>0){
          if (!haveA) a=f+b+c
          used=t-a
          pct=int(used*100/t)
          printf("[OK] Memory: %d%% used (%d / %d kB)\n", pct, used, t)
        } else { print "[WARN] Memory info unavailable" }
      }' /proc/meminfo
  else
    warn "No /proc/meminfo"
  fi
}

load_check() {
  LOAD=$(uptime | awk -F'load average: ' '{print $2}')
  [ -n "$LOAD" ] && ok "CPU Load: $LOAD" || warn "CPU load unknown"
}

uptime_human() {
  UP=$(uptime | awk -F'up ' '{print $2}' | awk -F',' '{print $1}')
  ok "Uptime: $UP"
}

case "$1" in
  status)  info "$NAME — $CODENAME"; kernel_check; mem_check; load_check; uptime_human ;;
  version) printf "%s %s (%s)\n" "$VERSION" "$CODENAME" "$BUILD_DATE" ;;
  *) echo "Usage: system.sh {status|version}"; exit 1 ;;
esac
