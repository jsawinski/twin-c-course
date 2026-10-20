#define __GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BREITE 60  // Breite des "Spielfeldes"
#define HOEHE 30   // Höhe des "Spielfeldes"

// ============================================================================
// random_numberen
// ============================================================================

/* Initialisierung des Zufallszahlengenerators
 */
void random_init() {
    srand(time(NULL));
}

/* Berechnung einer Zufallszahl zwischen min und max.
 */
int random_number(int min, int max) {
    return rand();
}

// ============================================================================
// Konsole
// ============================================================================

void konsole_loeschen() {
    printf("\x1b[2J");
}

void konsole_start() {
    printf("\x1b[H");
}

// ============================================================================
// Spielfeld
// ============================================================================

struct spielfeld {
    char daten[HOEHE][BREITE + 1];  // +1 für '\0' am Ende jeder Zeile
    int breite;
    int hoehe;
};

void spielfeld_anzeigen(struct spielfeld* feld) {
    for (int y = 0; y < feld->hoehe; y++) {
        printf("%s\n", feld->daten[y]);
    }
}

void spielfeld_setzen(struct spielfeld* feld, int x, int y, char c) {
    if (x >= 0 && x < feld->breite && y >= 0 && y < feld->hoehe) {
        feld->daten[y][x] = c;
    }
}

void spielfeld_zufaellig_fuellen(struct spielfeld* feld, char c, int anzahl) {
    for (int i = 0; i < anzahl; i++) {
        int x = random_number(0, feld->breite - 1);
        int y = random_number(0, feld->hoehe - 1);

        /* Sicherstellen, dass das Feld frei ist */
        while (feld->daten[y][x] != ' ') {
            x = random_number(0, feld->breite - 1);
            y = random_number(0, feld->hoehe - 1);
        }

        feld->daten[y][x] = c;
    }
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    struct spielfeld feld;

    /* Spielfeld initialisieren */
    feld.breite = BREITE;
    feld.hoehe = HOEHE;
    for (int y = 0; y < HOEHE; y++) {
        for (int x = 0; x < BREITE; x++) {
            feld.daten[y][x] = ' ';
        }
        feld.daten[y][BREITE] = '\0';  // Nullterminator für jede Zeile
    }

    konsole_loeschen();

    // Alle 0.1s wird ein Spielfeld mit einem '*' gefüllt.
    while (1) {
        // Ein zufälliges freies Feld auswählen
        int x, y;

        x = random_number(0, BREITE - 1);
        y = random_number(0, HOEHE - 1);

        while (feld.daten[y][x] != ' ') {
            x = random_number(0, BREITE - 1);
            y = random_number(0, HOEHE - 1);
        }

        feld.daten[y][x] = '*';

        // Spielfeld anzeigen
        konsole_start();
        for (int y = 0; y < HOEHE; y++) {
            printf("%s\n", feld.daten[y]);
        }

        fflush(stdout);
        usleep(100000);
    }

    return 0;
}
