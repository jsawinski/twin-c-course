#define __GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    for(int i = 1; i <= 10; i++) {
        int zahl = rand();
        printf("Zufallszahl %d: %d\n", i, (zahl % 6) + 1); 
    }

    return 0;
}




































// void zeichen(char c) {
//     printf("%c", c);
// }

// int main() {
//     int stern_x, stern_y;

//     konsole_loeschen();

//     while (1) {
//         stern_x = zufallszahl(0, BREITE - 1);
//         stern_y = zufallszahl(0, HOEHE - 1);

//         for(int t = 0; t < 5; t++) {       
//             konsole_start();

//             for (int y = 0; y < HOEHE; y++) {
//                 for (int x = 0; x < BREITE; x++) {
//                     if ((x == stern_x) && (y == stern_y)) {
//                         if (t == 0)
//                             zeichen('.');
//                         else 
//                             zeichen(' ');
//                     }
//                     else
//                         zeichen(' ');
//                 }
//                 printf("\n");
//             }

//             fflush(stdout);
//             usleep(500000);
//         }
//     }

//     return 0;
// }
