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

    // Zufallszahl von 1 bis 6
    int zahl = random_number(1, 6);

    // Ausgabe auf dem Bildschirm
    printf("%d\n", zahl);

    return 0;
}
