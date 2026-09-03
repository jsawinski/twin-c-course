#define __GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

#define HOEHE 20

void konsole_start() { 
    printf("\x1b[H"); 
}

void tropfen(int b) {
    if (b)
        printf("|");
    else
        printf(" ");
}

int main() {
    while (1) {
        for (int i = 0; i < HOEHE; i++) {
            konsole_start();
            for (int y = 0; y < HOEHE; y++) {
                tropfen((y == i));
                printf("\n");
            }

            fflush(stdout);
            usleep(100000);
        }
    }

    return 0;
}
