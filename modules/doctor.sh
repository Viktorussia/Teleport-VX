#!/bin/sh
ok()  { printf "✔ %s\n" "$1"; }
warn(){ printf "⚠ %s\n" "$1"; }
err() { printf "✖ %s\n" "$1"; }

run_doctor() {
  echo "── Teleport VX • Doctor ──"

  # 1) Базовая структура
  MISS=0
  for d in boot core docs style config logs bin modules; do
    if [ -d "$d" ]; then ok "dir: $d"; else warn "missing dir: $d"; MISS=1; fi
  done
  [ "$MISS" -eq 0 ] && ok "project structure looks good"

  # 2) Git: внутри репо?
  if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    ok "git: repository detected"
  else
    err "git: not a repository"; return 1
  fi

  # 3) Текущая ветка и статус
  BR=$(git rev-parse --abbrev-ref HEAD 2>/dev/null)
  SB=$(git status -sb 2>/dev/null | head -n1)
  echo "   branch: $BR"
  echo "   status: $SB"

  # 4) Remotes и доступность
  URL=$(git remote get-url origin 2>/dev/null)
  if [ -n "$URL" ]; then
    echo "   origin: $URL"
    if git ls-remote -h "$URL" HEAD >/dev/null 2>&1; then
      ok "remote reachable"
    else
      err "remote not reachable (check token / network)"
    fi
    echo "$URL" | grep -q "github_pat_" \
      && ok "fine-grained token present in remote URL" \
      || warn "token not detected in remote URL"
  else
    err "no origin remote configured"
  fi

  # 5) Исполняемые файлы
  [ -x bin/vx ] && ok "bin/vx is executable" || warn "bin/vx not executable"
  [ -x tools/autosave.sh ] && ok "autosave.sh is executable" || warn "autosave.sh not executable"

  # 6) Автор git
  UN=$(git config user.name)
  UE=$(git config user.email)
  [ -n "$UN" ] && ok "git user.name: $UN" || warn "git user.name not set"
  [ -n "$UE" ] && ok "git user.email: $UE" || warn "git user.email not set"

  # 7) Свободное место
  DF=$(df -h . 2>/dev/null | tail -1)
  echo "   disk: $DF"

  echo "── Doctor finished ──"
}
run_doctor
