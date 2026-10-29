# Ausgabe als PDF (Cairolatex für perfekte Schrift-Einbindung in LaTeX)
set terminal cairolatex pdf size 12cm, 8cm font ",10"

# Dateiname der Ausgabe
set output "images/physik/zuege.tex"

# Achsen und Beschriftung
set xlabel "Zeit t [h]"
set ylabel "Entfernung von Bonn [km]"
set grid

# Wertebereich
set xrange [0:1.5]
set yrange [0:350]

# Legende
set key top right box opaque

# Die Strecke Bonn-Stuttgart
d = 300
v1 = 100
v2 = -200

# Zug 1 (startet in Bonn, fährt nach Stuttgart)
# Formel: s_1 = v_1 * t
s1(x) = v1 * x

# Zug 2 (startet in Stuttgart (d=300), fährt nach Bonn)
# Formel: s_2 = d + v_2 * t
s2(x) = d + v2 * x

# Gestrichelte Linie vom Schnittpunkt (1, 100) zur x-Achse (y=0)
set arrow 1 from 1, 100 to 1, 0 nohead dt 2 lw 1.5 lc rgb "black"

# Gestrichelte Linie vom Schnittpunkt (1, 100) zur y-Achse (x=0)
set arrow 2 from 1, 100 to 0, 100 nohead dt 2 lw 1.5 lc rgb "black"

# Plotten
plot s1(x) title "Zug Bonn $\\rightarrow$ Stuttgart" lc rgb "#1f77b4" lw 2, \
     s2(x) title "Zug Stuttgart $\\rightarrow$ Bonn" lc rgb "#d62728" lw 2
