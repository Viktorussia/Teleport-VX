#!/bin/sh
set -e
# идти в корень проекта (скрипт лежит в tools)
cd "$(dirname "$0")/.."

# текущая ветка (если не найдётся — main)
BRANCH="$(git rev-parse --abbrev-ref HEAD 2>/dev/null || echo main)"

# сообщение коммита (можно передать своим аргументом)
MSG="${1:-autosave: $(date -u '+%Y-%m-%d %H:%M UTC')}"

# добавить всё изменённое/новое/удалённое
git add -A

# не коммитить, если нечего
if git diff --cached --quiet; then
  echo "✓ Нечего коммитить."
else
  git commit -m "$MSG"
fi

# пушим в origin на текущую ветку
git push -u origin "$BRANCH"
