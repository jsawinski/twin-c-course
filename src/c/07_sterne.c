#define __GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BREITE 60
#define HOEHE 30

void konsole_loeschen() { 
    printf("\x1b[2J"); 
}

void konsole_start() { 
    printf("\x1b[H"); 
}

int zufallszahl(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void zeichen(char c) {
    printf("%c", c);
}

int main() {
    int stern_x, stern_y;

    konsole_loeschen();

    while (1) {
        stern_x = zufallszahl(0, BREITE - 1);
        stern_y = zufallszahl(0, HOEHE - 1);

        for(int t = 0; t < 5; t++) {       
            konsole_start();

            for (int y = 0; y < HOEHE; y++) {
                for (int x = 0; x < BREITE; x++) {
                    if ((x == stern_x) && (y == stern_y)) {
                        if (t == 0)
                            zeichen('.');
                        else 
                            zeichen(' ');
                    }
                    else
                        zeichen(' ');
                }
                printf("\n");
            }

            fflush(stdout);
            usleep(500000);
        }
    }

    return 0;
}
