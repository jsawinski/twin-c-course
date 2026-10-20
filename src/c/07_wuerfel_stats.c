#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Hilfsfunktion, um den Zufallszahlengenerator zu initialisieren:
void random_init() {
    srand(time(NULL));
}

// Hilfsfunktion, um eine Zufallszahl im Bereich von min bis max zu erzeugen:
int random_number(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    random_init();

    // Speicher für die Häufigkeit einer bestimmten Zufallszahl
    int seiten[6] = {0, 0, 0, 0, 0, 0};

    // Die Schleife läuft durch alle möglichen Zufallszahlen
    // (also so lange, bis sich die Reihenfolge wiederholt):
    for (int i = 0; i < RAND_MAX; i++) {
        // Zufallszahl von 1 und 6
        int zahl = random_number(1, 6);

        // Speichern der Häufigkeit dieser Zahl
        ++seiten[zahl - 1];

        // Anzeige von i und wie oft die Zahlen 1 bis 6 bis jetzt
        // "gewürfelt" worden sind:
        printf("%8d: ", i);
        for (int s = 0; s < 6; s++) printf("%d ", seiten[s]);
        printf("\n");
    }

    return 0;
}