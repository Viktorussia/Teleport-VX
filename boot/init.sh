#!/bin/ash
. "$(dirname "$0")/../config/system.cfg"

printf "\033[1;36mBooting %s — %s\033[0m\n" "$NAME" "$CODENAME"
sleep 0.2
printf "[OK] Kernel: initialized\n";  sleep 0.2
printf "[OK] Memory: online\n";       sleep 0.2
printf "[OK] CPU: running\n";         sleep 0.2

echo
sh "$(dirname "$0")/../core/system.sh" status

echo
printf "\033[1;32mSystem Ready >\033[0m\n"
