C_RESET="\033[0m"; C_PURP="\033[35m"

banner() {
  local title="$1" right="$2"
  local cols="$(stty size 2>/dev/null | awk '{print $2}')" || true
  [ -z "$cols" ] && cols="${COLUMNS:-78}"
  local width=$((cols-1))
  [ $width -lt 20 ] && width=20
  printf "${C_PURP}%.*s${C_RESET}\n" "$width" "=================================================="
  printf "%s%s%s\n" "$title" "$(printf '%*s' $((width - ${#title} - ${#right})) '')" "$right"
  printf "${C_PURP}%.*s${C_RESET}\n" "$width" "=================================================="
}
# === Teleport VX :: UI Animations ===

# безопасная остановка фоновой джобы
_safe_stop() {
  pid="$1"
  [ -n "$pid" ] || return 0
  kill -0 "$pid" 2>/dev/null || return 0
  kill "$pid" 2>/dev/null
  wait "$pid" 2>/dev/null
}

# Спиннер: spinner_start "Текст..."  ;  spinner_ok "Готово" | spinner_fail "Ошибка"
spinner_start() {
  SPIN_MSG="$*"
  SPIN_FRAMES='-\|/'
  SPIN_PID=
  (
    i=0
    while :; do
      c=${SPIN_FRAMES:i%${#SPIN_FRAMES}:1}
      printf "\r[ %s ] %s" "$c" "$SPIN_MSG"
      i=$((i+1))
      sleep 0.1
    done
  ) &
  SPIN_PID=$!
  # сохраним PID экспортом для вызывающего скрипта
  echo "$SPIN_PID" > /tmp/.vx_spin.pid
}

spinner_ok() {
  pid="$(cat /tmp/.vx_spin.pid 2>/dev/null)"
  _safe_stop "$pid"
  printf "\r[ OK ] %s\n" "$*"
  rm -f /tmp/.vx_spin.pid
}

spinner_fail() {
  pid="$(cat /tmp/.vx_spin.pid 2>/dev/null)"
  _safe_stop "$pid"
  printf "\r[FAIL] %s\n" "$*"
  rm -f /tmp/.vx_spin.pid
}

# Прогресс-бар: progress cur total "Текст"
progress() {
  cur="$1"; total="$2"; shift 2
  msg="$*"
  cols="$(stty size 2>/dev/null | awk '{print $2}')"
  [ -z "$cols" ] && cols="${COLUMNS:-78}"
  width=$(( cols - 12 ))
  [ $width -lt 10 ] && width=10
  pct=$(( cur*100 / (total>0?total:1) ))
  filled=$(( width*pct/100 ))
  empty=$(( width-filled ))
  printf "\r[%.*s%.*s] %3d%% %s" "$filled" "########################################" "$empty" "                                        " "$pct" "$msg"
  [ "$cur" -ge "$total" ] && printf "\n"
}
# === Teleport VX :: Pulse Monitor ===

pulse_monitor() {
  echo
  echo "CPU Pulse Monitor :: Teleport VX"
  echo "Press Ctrl+C to stop"
  echo "---------------------------------"

  while true; do
    # CPU load (avg over 1m)
    load=$(awk '{print $1}' /proc/loadavg 2>/dev/null)
    [ -z "$load" ] && load="0.0"

    # Цвета по уровню загрузки
    if (( $(echo "$load < 0.7" | bc -l) )); then
      color="\033[32m"   # зелёный
    elif (( $(echo "$load < 1.5" | bc -l) )); then
      color="\033[33m"   # жёлтый
    else
      color="\033[31m"   # красный
    fi

    # Анимация точки (пульса)
    frame=$(( (frame + 1) % 4 ))
    case $frame in
      0) sym="." ;;
      1) sym="o" ;;
      2) sym="O" ;;
      3) sym="o" ;;
    esac

    # Очистка строки и вывод
    printf "\r${color}♥ CPU: %s | Pulse: %s${C_RESET}" "$load" "$sym"
    sleep 0.3
  done
}
# === Teleport VX :: Pulse Monitor (BusyBox-safe) ===

pulse_monitor() {
  echo
  echo "CPU Pulse Monitor :: Teleport VX"
  echo "Press Ctrl+C to stop"
  echo "---------------------------------"

  frame=0
  while true; do
    load=$(awk '{print $1}' /proc/loadavg 2>/dev/null)
    [ -z "$load" ] && load="0.0"

    # Проверка уровня нагрузки без (( ))
    if awk "BEGIN {exit !($load < 0.7)}"; then
      color="\033[32m"  # зелёный
    elif awk "BEGIN {exit !($load < 1.5)}"; then
      color="\033[33m"  # жёлтый
    else
      color="\033[31m"  # красный
    fi

    # Анимация точек
    frame=$(( (frame + 1) % 4 ))
    case "$frame" in
      0) sym="." ;;
      1) sym="o" ;;
      2) sym="O" ;;
      3) sym="o" ;;
    esac

    printf "\r${color}♥ CPU: %s | Pulse: %s${C_RESET}" "$load" "$sym"
    sleep 0.3
  done
}
