#!/usr/bin/env ash
# Teleport VX — System Doctor

echo "Teleport VX — System Doctor"
echo

# Kernel
printf "[OK] Kernel: active (ash/busybox)\n"

# Memory (из /proc/meminfo)
awk '
/MemTotal:/ {t=$2}
/MemAvailable:/ {a=$2}
END{
  if(t>0){
     used=t-a; pct=int(used*100/t)
     printf("[OK] Memory: %d%% used (%d / %d kB)\n", pct, used, t)
  } else {
     print "[WARN] Memory info unavailable"
  }
}' /proc/meminfo

# CPU load (uptime)
LOAD=$(uptime | awk -F'load average: ' '{print $2}' | cut -d, -f1-3)
printf "[OK] CPU Load: %s\n" "$LOAD"

# Uptime (коротко)
UP=$(uptime | awk -F'up ' '{print $2}' | awk -F',' '{print $1}')
printf "[OK] Uptime: %s\n" "$UP"

# Сеть (ping)
if ping -c1 -W1 1.1.1.1 >/dev/null 2>&1; then
  echo "[OK] Network: online (ping 1.1.1.1)"
else
  echo "[WARN] Network: offline (no ping)"
fi

# Проверка обновлений локального репо
if git -C "$HOME/teleport-vx" fetch --quiet 2>/dev/null; then
  LOCAL=$(git -C "$HOME/teleport-vx" rev-parse @ 2>/dev/null)
  REMOTE=$(git -C "$HOME/teleport-vx" rev-parse @{u} 2>/dev/null)
  BASE=$(git -C "$HOME/teleport-vx" merge-base @ @{u} 2>/dev/null)
  if [ "$LOCAL" = "$REMOTE" ]; then
    echo "[OK] Repo: up-to-date with origin/main"
  elif [ "$LOCAL" = "$BASE" ]; then
    echo "[INFO] Repo: updates available (run: vx update)"
  elif [ "$REMOTE" = "$BASE" ]; then
    echo "[INFO] Repo: local commits ahead (run: vx sync)"
  else
    echo "[WARN] Repo: diverged (run: git pull --rebase)"
  fi
else
  echo "[WARN] Repo: cannot fetch origin"
fi

echo
echo "System check complete. Neon Aurora ready."
