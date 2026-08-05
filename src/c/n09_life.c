#define __GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

static struct termios einstellungen;

void konsole_loeschen() { 
    printf("\x1b[2J"); 
}

void konsole_start() { 
    printf("\x1b[H"); 
}

void konsole_cursor_aus() {
    printf("\x1b[?25l");
}

void konsole_cursor_an() {
    printf("\x1b[?25h");
}

void konsole_initialisieren() {
    /* Konsolen einstellen */
    tcgetattr(STDIN_FILENO, &einstellungen);
    struct termios neue_einstellungen = einstellungen;

    neue_einstellungen.c_lflag &= ~(ICANON | ECHO /*| ISIG*/); // Deaktiviert Canonical Mode und Echo
    neue_einstellungen.c_cc[VMIN] = 0;  // Mindestens 1 Zeichen zum Lesen
    neue_einstellungen.c_cc[VTIME] = 0; // Kein Timeout

    tcsetattr(STDIN_FILENO, TCSANOW, &neue_einstellungen);

    /* Cursor ausschalten */
    konsole_cursor_aus();
}

int kbhit(void) {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    
    // Prüft, ob Daten auf stdin anstehen
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

int getch_nb(void) {
    if (!kbhit()) {
        return -1;  // Keine Taste gedrückt
    }
    
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

void konsole_zuruecksetzen() {
    tcsetattr(STDIN_FILENO, TCSANOW, &einstellungen);
    konsole_cursor_an();
}

int zufallszahl(int min, int max) {
    return rand() % (max - min + 1) + min;
}

struct spielfeld {
    char *daten;  // +1 für '\0' am Ende jeder Zeile
    int breite;
    int hoehe;
};

void spielfeld_initialisieren(struct spielfeld *feld, int breite, int hoehe) {
    feld->breite = breite;
    feld->hoehe = hoehe;
    feld->daten = malloc(hoehe * (breite + 1) * sizeof(char));
    for (int y = 0; y < hoehe; y++) {
        for (int x = 0; x < breite; x++) {
            feld->daten[y * (breite + 1) + x] = ' ';
        }
        feld->daten[y * (breite + 1) + breite] = '\0';  // Nullterminator für jede Zeile
    }
}

void spielfeld_anzeigen(struct spielfeld *feld) {
    for (int y = 0; y < feld->hoehe; y++) {
        printf("%s", &feld->daten[y * (feld->breite + 1)]);
    }
}

void spielfeld_setzen(struct spielfeld *feld, int x, int y, char c) {
    if (x >= 0 && x < feld->breite && y >= 0 && y < feld->hoehe) {
        feld->daten[y * (feld->breite + 1) + x] = c;
    }
}

char spielfeld_inhalt(struct spielfeld *feld, int x, int y) {
    if (x >= 0 && x < feld->breite && y >= 0 && y < feld->hoehe) {
        return feld->daten[y * (feld->breite + 1) + x];
    }
    return '\0'; // Rückgabe eines Nullzeichens, wenn die Koordinaten außerhalb des Spielfelds liegen
}

void spielfeld_leeren(struct spielfeld *feld) {
    for (int y = 0; y < feld->hoehe; y++) {
        for (int x = 0; x < feld->breite; x++) {
            feld->daten[y * (feld->breite + 1) + x] = ' ';
        }
    }
}

void spielfeld_zufaellig_fuellen(struct spielfeld *feld, char c, int anzahl) {
    for (int i = 0; i < anzahl; i++) {
        int x = zufallszahl(0, feld->breite - 1);
        int y = zufallszahl(0, feld->hoehe - 1);

        /* Sicherstellen, dass das Feld frei ist */
        for (int k=0; (k<1000) && (spielfeld_inhalt(feld, x, y) != ' '); k++) {
            x = zufallszahl(0, feld->breite - 1);
            y = zufallszahl(0, feld->hoehe - 1);
        }

        spielfeld_setzen(feld, x, y, c);
    }
}

int spielfeld_nachbarn(struct spielfeld *feld, int x, int y) {
    int lebende_nachbarn = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue; // Überspringe die Zelle selbst
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < feld->breite && ny >= 0 && ny < feld->hoehe) {
                if (spielfeld_inhalt(feld, nx, ny) == '*') {
                    lebende_nachbarn++;
                }
            }
        }
    }
    return lebende_nachbarn;
}

#define UNTERBEVOELKERUNG 2
#define REPRODUKTION 3
#define UEBERBEVOELKERUNG 4


int main() {
    struct winsize w;
    struct spielfeld feld;
    int pausenzeit = 100000; // Standardpausenzeit in Mikrosekunden
    
    /* Terminalgröße abfragen und Spielfeld initialisieren */
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        /* Ein Fehler ist aufgetreten. */
        return 1;
    }
    spielfeld_initialisieren(&feld, w.ws_col, w.ws_row);

    printf("Terminalgröße: %d Spalten, %d Zeilen\n", w.ws_col, w.ws_row);

    /* Konsole initialisieren und sicherstellen, dass sie beim Beenden zurückgesetzt wird */
    konsole_initialisieren();
    atexit(konsole_zuruecksetzen);

    while (1) {
        {
            konsole_start();

            // Spiel des Lebens Logik (siehe https://de.wikipedia.org/wiki/Conways_Spiel_des_Lebens)
            for(int x=0; x<feld.breite; x++) {
                for(int y=0; y<feld.hoehe; y++) {
                    int nachbarn = spielfeld_nachbarn(&feld, x, y);
                    char aktueller_zustand = spielfeld_inhalt(&feld, x, y);
                    if (aktueller_zustand == '*') {
                        if (nachbarn < UNTERBEVOELKERUNG || nachbarn >= UEBERBEVOELKERUNG) {
                            spielfeld_setzen(&feld, x, y, ' '); // Zelle stirbt
                        }
                    } else {
                        if (nachbarn == REPRODUKTION) {
                            spielfeld_setzen(&feld, x, y, '*'); // Zelle wird lebendig
                        }
                    }
                }
            }

            spielfeld_anzeigen(&feld);
        }

        {
            int c = getch_nb();
            if (c != -1) {
                if (c == 'q') {
                    break;  
                }
                else if (c == 'n') { // "NEU"
                    spielfeld_leeren(&feld); 
                    spielfeld_zufaellig_fuellen(&feld, '*', (feld.breite*feld.hoehe)/20); // 5% der Felder zufällig füllen
                    spielfeld_anzeigen(&feld);
                }
                else if (c == 'm') { // "MEHR"
                    spielfeld_zufaellig_fuellen(&feld, '*', (feld.breite*feld.hoehe)/20); // 5% der Felder zufällig füllen
                    spielfeld_anzeigen(&feld);
                }
                else if (c == 'l') { // "LANGSAMER"
                    if (pausenzeit < 200000) {
                        pausenzeit += 10000; // Verlangsamen
                    }
                }
                else if (c == 's') { // "SCHNELLER"
                    if (pausenzeit >= 10000) {
                        pausenzeit -= 10000; // Beschleunigen
                    }
                }
            }
        }

        fflush(stdout);
        usleep(pausenzeit);
    }

    return 0;
}




