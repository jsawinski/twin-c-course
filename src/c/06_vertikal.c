#define __GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

// Makro für die Anzahl der Zeilen, die das Lauflicht laufen soll
#define HOEHE 20

// Hilfsfunktion: springe in der Konsole in die 1. Zeile und 1. Spalte
void konsole_start() { 
    printf("\x1b[H"); 
}

// Hilfsfunktion: Ausgabe eines "Tropfens" oder eines Leerzeichens
void tropfen(int b) {
    if (b)
        printf("|");
    else
        printf(" ");
}

int main() {
    // Das Lauflicht läuft, bis es durch Strg+C abgebrochen wird
    while (1) {
        // Schleife i: Zeile, in der der "Tropfen" erscheinen soll
        for (int i = 0; i < HOEHE; i++) {
            konsole_start();

            // Ausgabe der Leerzeichen oder "Tropfen"
            for (int y = 0; y < HOEHE; y++) {
                tropfen((y == i));
                printf("\n");
            }

            // Puffer leeren
            fflush(stdout);

            // Kleine Pause
            usleep(100000);
        }
    }

    return 0;
}
