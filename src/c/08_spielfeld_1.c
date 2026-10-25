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
    // Euer Code
    return 0;
}