#!/usr/bin/env ash
# Teleport VX — Net Tools

case "$1" in
  ping)
    host="${2:-1.1.1.1}"
    echo "[Net] Pinging $host ..."
    ping -c3 "$host";;
  ip)
    echo "[Net] Interfaces:"
    ip addr 2>/dev/null || ifconfig 2>/dev/null || echo "no ip/ifconfig";;
  http)
    url="${2:-https://example.org}"
    if command -v curl >/dev/null 2>&1; then
      echo "[Net] HTTP GET $url"
      curl -I --max-time 5 "$url"
    else
      echo "[WARN] curl not installed (apk add curl)"
    fi;;
  *)
    cat <<HLP
Teleport VX — Net Tools
Usage:
  vx net ping [host]   # ping тест
  vx net ip            # показать интерфейсы
  vx net http [url]    # быстрый HTTP-запрос (требует curl)
HLP
    ;;
esac
