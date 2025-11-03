# 🪐 Teleport VX System

**Version:** 2.1 — Neon Aurora Build  
**Author:** Viktor Nagornyi  
**Platform:** Alpine / iSH  
**Language:** C  

Teleport VX — это минималистичная система эмуляции загрузки и оболочки, 
созданная вручную для обучения и экспериментов с псевдо-OS интерфейсом.  

## ✨ Features
- Три визуальных стиля: `classic`, `matrix`, `cyber`, `neon`  
- Анимация загрузки, приветствие пользователя  
- Смена темы командой `style <имя>`  
- Автозапуск при старте сессии  

## ⚙️ Usage
```bash
./teleport         # запуск
style matrix       # смена темы
boot               # перезапуск
exit               # выход
gcc teleport2.c -O2 -o teleport
Проверь содержимое:
```bash
cat README.md
cat > .gitignore <<'EOF'
# build artifacts
teleport
*.o
*.out

# editor backups
*~
*.swp

# system files
.DS_Store
