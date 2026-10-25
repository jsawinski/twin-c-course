# Ausgabe als PDF (Cairolatex für perfekte Schrift-Einbindung in LaTeX)
set terminal cairolatex pdf size 12cm, 8cm font ",10"
set output "physik/images/freierfall.tex"

# Achsen und Beschriftung
set xlabel "Zeit t [s]"
set ylabel "Höhe h [m]" textcolor rgb "#1f77b4"
set y2label "Geschwindigkeit v [m/s]" textcolor rgb "#d62728"

# Achsen-Bereiche
set xrange [0:50]
set yrange [0:10500]
set y2range [0:500]

# Achsen-Ticks (y1 blau, y2 rot)
set ytics nomirror textcolor rgb "#1f77b4"
set y2tics nomirror textcolor rgb "#d62728"
set grid

# Legende
set key top right box opaque

# Physikalische Konstanten
h0 = 10000.0
g = 9.81
v_schall = 343.0

# Formeln für den freien Fall
h(t) = h0 - 0.5 * g * t**2
v(t) = g * t

# Eine horizontale Linie für die Schallmauer auf der rechten Achse
# (wir plotten sie als Konstante auf der y2-Achse)
schall(t) = v_schall

# Berechne die Zeit, zu der die Schallmauer durchbrochen wird
t_schall = v_schall / g

# Gestrichelte Hilfslinie zum Durchbruch der Schallmauer
set arrow 1 from t_schall, first 0 to t_schall, second v_schall nohead dt 2 lw 1.5 lc rgb "black"

# Plotten
plot h(x) axes x1y1 title "Höhe" lc rgb "#1f77b4" lw 2, \
     v(x) axes x1y2 title "Geschwindigkeit" lc rgb "#d62728" lw 2, \
     schall(x) axes x1y2 title "Schallmauer" lc rgb "black" dt 3 lw 1.5