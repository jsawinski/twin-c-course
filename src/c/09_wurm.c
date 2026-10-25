#define __GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BREITE 60  // Breite des "Spielfeldes"
#define HOEHE 30   // Höhe des "Spielfeldes"

// ====================================================================
// Zufallszahlen
// ====================================================================

/* Initialisierung des Zufallszahlengenerators
 */
void random_init() {
    srand(time(NULL));
}

/* Berechnung einer Zufallszahl zwischen min und max.
 */
int random_number(int min, int max) {
    return min + rand() % (max - min + 1);
}

// ====================================================================
// Konsole
// ====================================================================

/* Löschen des gesamten Inhalts der Konsole.
 */
void konsole_loeschen() {
    printf("\x1b[2J");
}

/* An die Stelle (1,1) (Zeile,Spalte) in der Konsole springen.
 */
void konsole_start() {
    printf("\x1b[H");
}

/* Den Cursor in einer bestimmten Spalte und Zeile positionieren.
 * (Bei Koordinaten kommt immer die horizontale vor der vertikalen Position.)
 */
void konsole_gehe(int spalte, int zeile) {
    printf("\x1b[%d;%dH", zeile, spalte);
}

/* Ein Zeichen ausgeben.
 */
void konsole_zeichen(int ch) {
    printf("%c", ch);
    fflush(stdout);
}

// ====================================================================
// MAIN
// ====================================================================

int main() {
    random_init();

    konsole_loeschen();

    int zeile = random_number(1, HOEHE);
    int spalte = random_number(1, BREITE);
    
    printf("\x1b[%d;%dH", zeile, spalte);
    printf("\x1b[7m");

    int alte_richtung = 0;
    while (1) {
        int richtung = random_number(0, 3);

        int tmp = alte_richtung ^ richtung;
        // Up/Down vs. Sideways        +/-
        // 0 | 0 0 Same orientation    0 | 0 0
        // 1 | 0 1                     1 | 0 1 reverse direction
        // 1 | 1 0                     1 | 1 0 reverse direction
        // 0 | 1 1 Same orientation    0 | 1 1

        if ((~tmp & 2) && (tmp & 1)) richtung = alte_richtung;

        int wiederholung = random_number(5, 15);
        for (int i = 0; i < wiederholung; i++) {
            switch (richtung) {
                case 0:
                    printf("\x1b[A");
                    break;
                case 1:
                    printf("\x1b[B");
                    break;
                case 2:
                    printf("\x1b[C");
                    break;
                case 3:
                    printf("\x1b[D");
                    break;
            }

            printf(" \x1b[D");
            fflush(stdout);

            usleep(1000);
        }

        alte_richtung = richtung;
    }

    return 0;
}