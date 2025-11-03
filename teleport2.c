#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static const char *STYLEFILE = "/root/teleport-vx/.style";

static void spinner(const char *msg, int loops) {
    const char spin[] = "|/-\\";
    printf("\033[1;36m%s\033[0m ", msg);
    fflush(stdout);
    for (int i=0;i<loops;i++){
        printf("\b\033[1;34m%c\033[0m", spin[i%4]);
        fflush(stdout);
        usleep(120000);
    }
    printf("\b \n");
}

static void header_neon() {
    // Neon Aurora — чередуем фуксию и бирюзу
    printf("\n\033[1;95m┏ NEON AURORA ┓\033[0m  \033[1;96mTELEPORT VX\033[0m\n");
    printf("\033[1;92m[OK]\033[0m Kernel: \033[1;97minitialized\033[0m\n");
    printf("\033[1;92m[OK]\033[0m Memory: \033[1;96monline\033[0m\n");
    printf("\033[1;92m[OK]\033[0m CPU:    \033[1;95mrunning\033[0m\n\n");
}

static void header_cyber() {
    printf("\n\033[1;94m╒ CYBER BLUE ╕\033[0m  \033[1;37mTELEPORT VX\033[0m\n");
    printf("\033[1;92m[OK]\033[0m Kernel: initialized\n");
    printf("\033[1;92m[OK]\033[0m Memory: \033[1;32monline\033[0m\n");
    printf("\033[1;92m[OK]\033[0m CPU:    running\n\n");
}

static void header_matrix() {
    printf("\n\033[1;32m[MATRIX MODE]  TELEPORT VX\033[0m\n");
    printf("\033[1;32m[OK]\033[0m Kernel: initialized\n");
    printf("\033[1;32m[OK]\033[0m Memory: online\n");
    printf("\033[1;32m[OK]\033[0m CPU:    running\n\n");
}

static void header_classic() {
    printf("\n\033[1;36mTELEPORT VX SYSTEM BOOT\033[0m\n");
    printf("\033[1;32m[OK]\033[0m Kernel: initialized\n");
    printf("\033[1;32m[OK]\033[0m Memory: online\n");
    printf("\033[1;32m[OK]\033[0m CPU:    running\n\n");
}

static void boot_sequence(const char *style){
    printf("\033[2J\033[H");           // clear screen
    spinner("Booting", 10);
    if (!strcmp(style,"neon"))     header_neon();
    else if (!strcmp(style,"cyber"))  header_cyber();
    else if (!strcmp(style,"matrix")) header_matrix();
    else header_classic();
    printf("Welcome, Viktor.\n\033[1;36mSystem Ready >\033[0m\n");
}

static void save_style(const char *s){
    FILE *f=fopen(STYLEFILE,"w");
    if (f){ fputs(s,f); fclose(f); }
}

static void load_style(char *buf, size_t n){
    FILE *f=fopen(STYLEFILE,"r");
    if (f){ fgets(buf,n,f); fclose(f); }
    else { strncpy(buf,"cyber",n); buf[n-1]='\0'; }
    // trim
    size_t L=strlen(buf);
    while(L && (buf[L-1]=='\n'||buf[L-1]=='\r'||buf[L-1]==' ')) buf[--L]='\0';
}

int main(int argc, char **argv){
    char style[16]; load_style(style,sizeof(style));

    if (argc>1){
        if (!strcmp(argv[1],"help")){
            printf("Commands:\n");
            printf("  style <classic|matrix|cyber|neon>\n");
            printf("  boot           # show boot screen\n");
            printf("  exit           # quit\n");
            return 0;
        } else if (!strcmp(argv[1],"boot")){
            boot_sequence(style); return 0;
        } else if (!strcmp(argv[1],"style") && argc>2){
            if (!strcmp(argv[2],"classic")||!strcmp(argv[2],"matrix")||
                !strcmp(argv[2],"cyber")  ||!strcmp(argv[2],"neon")){
                strncpy(style,argv[2],sizeof(style)); style[sizeof(style)-1]='\0';
                save_style(style);
                printf("Style set to %s\n", style);
                // эффект мягкой перезагрузки
                spinner("Rebooting Teleport VX", 8);
                boot_sequence(style);
                return 0;
            } else {
                printf("Unknown style. Use: classic, matrix, cyber, neon\n");
                return 1;
            }
        }
    }

    // По умолчанию — просто показать текущую заставку
    boot_sequence(style);
    return 0;
}
