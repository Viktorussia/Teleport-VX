#include <stdio.h>
#include <unistd.h>
#include <stddef.h>

int main() {
    printf("\033[1;36mTELEPORT VX SYSTEM BOOT\n\033[0m");
    sleep(1);
    printf("\033[0;32m[OK] Kernel: initialized\n\033[0m");
    sleep(1);
    printf("\033[0;32m[OK] Memory: online\n\033[0m");
    sleep(1);
    printf("\033[0;32m[OK] CPU: running\n\033[0m");
    sleep(1);
    printf("\033[1;37mWelcome, Viktor.\n\033[0m");
    sleep(1);
    printf("\033[1;34mSystem Ready >\033[0m\n");
    return 0;
}
