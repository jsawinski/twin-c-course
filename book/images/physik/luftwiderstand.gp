# Ausgabe als PDF (Cairolatex für perfekte Schrift-Einbindung)
set terminal cairolatex pdf size 12cm, 8cm font ",10"
set output "images/physik/luftwiderstand.tex"

# Achsen und Beschriftung
set xlabel "Geschwindigkeit v [m/s]"
set ylabel "Kraft F [μN]" textcolor rgb "#333333"

# Wertebereiche
set xrange [0:10]
set yrange [0:20]

set grid
set key top left box opaque

# Physikalische Konstanten
rho_air = 1.225   # Dichte der Luft in kg/m^3
g = 9.81          # Erdbeschleunigung in m/s^2
cw = 0.4          # Widerstandsbeiwert

# --- TROPFEN (Durchmesser 1 mm) ---
d_tropfen = 0.001 # in m
r_tropfen = d_tropfen / 2.0
A_tropfen = pi * r_tropfen**2
V_tropfen = (4.0/3.0) * pi * r_tropfen**3
m_tropfen = 1000.0 * V_tropfen # Masse in kg
Fg_tropfen = m_tropfen * g * 1e6 # Gewichtskraft in μN

# --- SANDKORN (Durchmesser 1 mm) ---
d_sand = 0.001 # in m
r_sand = d_sand / 2.0
A_sand = pi * r_sand**2
V_sand = (4.0/3.0) * pi * r_sand**3
m_sand = 2650.0 * V_sand # Masse in kg
Fg_sand = m_sand * g * 1e6 # Gewichtskraft in μN

# Luftwiderstandskraft als Funktion der Geschwindigkeit (in μN)
Fw(v) = 0.5 * cw * A_tropfen * rho_air * v**2 * 1e6

# --- BERECHNUNG DER SCHNITTPUNKTE (Endgeschwindigkeiten) ---
# Fw(v) = Fg  =>  v = sqrt(Fg / (0.5 * cw * A * rho))
v_end_tropfen = sqrt((Fg_tropfen * 1e-6) / (0.5 * cw * A_tropfen * rho_air))
v_end_sand = sqrt((Fg_sand * 1e-6) / (0.5 * cw * A_sand * rho_air))

# --- VERTIKALE HILFSLINIEN ---
# Pfeil 1: Vom Schnittpunkt Tropfen zur x-Achse
set arrow 1 from v_end_tropfen, Fg_tropfen to v_end_tropfen, 0 nohead dt 2 lw 1.5 lc rgb "#1f77b4" front

# Pfeil 2: Vom Schnittpunkt Sandkorn zur x-Achse
set arrow 2 from v_end_sand, Fg_sand to v_end_sand, 0 nohead dt 2 lw 1.5 lc rgb "#2ca02c" front

# Plotten
plot Fw(x) title "Luftwiderstand" lc rgb "#d62728" lw 2, \
     Fg_tropfen title "Gewichtskraft Tropfen" lc rgb "#1f77b4" dt 2 lw 1.5, \
     Fg_sand title "Gewichtskraft Sandkorn" lc rgb "#2ca02c" dt 3 lw 1.5