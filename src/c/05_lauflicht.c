#define __GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main() {
    // Das Lauflicht wird so lange wiederholt,
    // bis man "Strg-C" drückt.
    while (1) {
        // Zähler für das Lauflicht (Breite von 20 Zeichen)
        for (int i = 0; i < 20; i++) {
            // An den Zeilenanfang zurückkehren
            printf("\r");

            // Ausgabe eines Leerzeichens oder Sternes
            // (genau da, wo i == j ist, ein Stern)
            for (int j = 0; j < 20; j++) {
                if (i == j)
                    printf("*");
                else
                    printf(" ");
            }

            // Zeichen ausgeben (Puffer leeren)
            fflush(stdout);

            // Pause von 0.1 Sekunden
            // (das Lauflicht braucht also 2 Sekunden für einen Durchlauf)
            usleep(100000);
        }
    }

    return 0;
}
