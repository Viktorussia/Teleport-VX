#!/usr/bin/env ash
# Teleport VX — TUI Menu (простое текстовое меню)

while :; do
  clear
  echo "Teleport VX — Control Center"
  echo "1) System Doctor"
  echo "2) Net Tools (ping 1.1.1.1)"
  echo "3) Show Status"
  echo "4) Exit"
  printf "> "
  read ans
  case "$ans" in
    1) vx doctor; read _ ;;
    2) vx net ping 1.1.1.1; read _ ;;
    3) vx status; read _ ;;
    4) exit 0 ;;
    *) echo "Unknown option"; sleep 1 ;;
  esac
done
