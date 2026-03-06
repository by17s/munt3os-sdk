#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sys/socket.h"
#include "../sys/syscalls.h"
#include "../sys/sysdef.h"

// ANSI цветовые коды
#define C_RESET   "\033[0m"
#define C_LOGO    "\033[1;36m"  
#define C_TITLE   "\033[1;35m"  
#define C_LABEL   "\033[1;34m"  
#define C_TEXT    "\033[0m"    

int main() {
    // 1. Читаем реальные данные (CPU)
    char cpuname[128] = "Unknown CPU";
    FILE* f = fopen("/proc/cpuname", "r");
    if (f) {
        size_t bytes = fread(cpuname, 1, sizeof(cpuname) - 1, f);
        if (bytes > 0) {
            if (cpuname[bytes - 1] == '\n') {
                cpuname[bytes - 1] = '\0';
            } else {
                cpuname[bytes] = '\0';
            }
        }
        fclose(f);
    }

    char os_name[128] = "Unknown OS";
    f = fopen("/proc/os-name", "r");
    if (f) {
        fread(os_name, 1, sizeof(os_name) - 1, f);
        fclose(f);
    }

    char kernel[128] = "Unknown Kernel";
    char kernel_name[64] = "Unk";
    f = fopen("/proc/krnl-name", "r");
    if (f) {
        fread(kernel_name, 1, sizeof(kernel_name) - 1, f);
        fclose(f);
    }

    char kernel_ver[16] = "0.0.0";
    f = fopen("/proc/krnl-version", "r");
    if (f) {
        fread(kernel_ver, 1, sizeof(kernel_ver) - 1, f);
        snprintf(kernel, sizeof(kernel), "%s-%s", kernel_ver, kernel_name);
        fclose(f);
    }

    char memory[128] = "Unk";
    f = fopen("/proc/mem", "r");
    if (f) {
        size_t bytes = fread(memory, 1, sizeof(memory) - 1, f);
        if (bytes > 0) {
            if (memory[bytes - 1] == '\n') {
                memory[bytes - 1] = '\0';
            } else {
                memory[bytes] = '\0';
            }
        }
        fclose(f);
    }

    char uptime[128];
    f = fopen("/proc/uptime", "r");
    if (f) {
        size_t bytes = fread(uptime, 1, sizeof(uptime) - 1, f);
        if (bytes > 0) {
            if (uptime[bytes - 1] == '\n') {
                uptime[bytes - 1] = '\0';
            } else {
                uptime[bytes] = '\0';
            }
        }
        int64_t uptime_sec = atoll(uptime);
        int64_t minutes = uptime_sec / 60;
        int64_t hours = minutes / 60;
        int64_t sec = uptime_sec % 60;
        if (hours > 0) {
            snprintf(uptime, sizeof(uptime), "%ld H %ld m %ld s", hours, minutes % 60, sec);
        } else {
            snprintf(uptime, sizeof(uptime), "%ld m %ld s", minutes, sec);
        }
        fclose(f);
    }

    // 2. Заглушки для остальных данных
    const char *username = "by17s";
    const char *hostname = "munt3os";
    const char *shell    = "UxSh";

    // 3. Массив с логотипом (обратные слеши нужно экранировать: \\)
    const char *logo[] = {
        " /$$      /$$  /$$$$$$   /$$$$$$ ",
        "| $$$    /$$$ /$$__  $$ /$$__  $$",
        "| $$$$  /$$$$| $$  \\ $$| $$  \\__/",
        "| $$ $$/$$ $$| $$  | $$|  $$$$$$ ",
        "| $$  $$$| $$| $$  | $$ \\____  $$",
        "| $$\\  $ | $$| $$  | $$ /$$  \\ $$",
        "| $$ \\/  | $$|  $$$$$$/|  $$$$$$/",
        "|__/     |__/ \\______/  \\______/ "
    };

    int logo_lines = sizeof(logo) / sizeof(logo[0]);

    printf("\n");

    // 4. Выводим строку за строкой: кусок логотипа + кусок информации
    for (int i = 0; i < logo_lines; i++) {
        // Печатаем строку логотипа с фиксированной шириной (например, 35 символов), чтобы текст был выровнен
        printf("%s%-35s" C_RESET " ", C_LOGO, logo[i]);

        // Печатаем соответствующую строку информации
        switch (i) {
            case 0:
                printf("%s%s@%s" C_RESET "\n", C_TITLE, username, hostname);
                break;
            case 1:
                printf("---------------\n");
                break;
            case 2:
                printf("%sOS:" C_TEXT " %s\n", C_LABEL, os_name);
                break;
            case 3:
                printf("%sKernel:" C_TEXT " %s\n", C_LABEL, kernel);
                break;
            case 4:
                printf("%sUptime:" C_TEXT " %s\n", C_LABEL, uptime);
                break;
            case 5:
                printf("%sShell:" C_TEXT " %s\n", C_LABEL, shell);
                break;
            case 6:
                printf("%sCPU:" C_TEXT " %s\n", C_LABEL, cpuname);
                break;
            case 7:
                printf("%sMemory:" C_TEXT " %s\n", C_LABEL, memory);
                break;
            default:
                printf("\n");
                break;
        }
    }

    printf("\n");
    printf("                                    ");
    printf("\033[41m   \033[42m   \033[43m   \033[44m   \033[45m   \033[46m   \033[47m   \033[0m\n\n");

    return 0;
}