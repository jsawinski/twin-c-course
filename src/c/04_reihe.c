/** Berechnung von Pi/4 aus der Reihe 1 - 1/3 + 1/5 - 1/7 + ... */

#include <stdio.h>

int main() {
    double pi = 1.0;
    for (int i = 1; i <= 1000000000; i++) {
        double n = 2*i + 1;     // 3, 5, 7, 9, ...
        n = 1.0 / n;            // 1/n

        // Ausgabe der Zwischenergebnisse
        printf("%9d Pi: %.15f  (% .15f)\n", i, 4*pi, 4*pi - 3.14159265358979323846);

        if (i & 1)
            pi -= n;
        else
            pi += n;
    }   
    return 0;
}
