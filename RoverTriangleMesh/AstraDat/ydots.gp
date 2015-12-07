set termoption dash
set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "ydots"
set arrow from 30,-100 to 30,45 lw 0.5 lt 2 lc 1 nohead
plot\
"YDOTS.dat" u 1:2 t "Trunk y velocity" w l lt 1,\
"YDOTS.dat" u 1:3 t "Trunk x velocity" w l lt 1 lc rgb "blue",\
"YDOTS.dat" u 1:4 t "Trunk z velocity" w l lt 1 lc rgb "green",\
"YDOTS.dat" u 1:5 t "Trunk y velocity" w l lt 1,\
"YDOTS.dat" u 1:6 t "Trunk x velocity" w l lt 1 lc rgb "blue",\
"YDOTS.dat" u 1:7 t "Trunk z velocity" w l lt 1 lc rgb "green",\
"YDOTS.dat" u 1:8 t "Trunk y velocity" w l lt 1,\
"YDOTS.dat" u 1:9 t "Trunk x velocity" w l lt 1 lc rgb "blue",\
"YDOTS.dat" u 1:10 t "Trunk z velocity" w l lt 1 lc rgb "green",\
"YDOTS.dat" u 1:11 t "Trunk y velocity" w l lt 1,\
"YDOTS.dat" u 1:12 t "Trunk x velocity" w l lt 1 lc rgb "blue",\
"YDOTS.dat" u 1:13 t "Trunk z velocity" w l lt 1 lc rgb "green",\
"YDOTS.dat" u 1:14 t "Trunk y velocity" w l lt 1,\
"YDOTS.dat" u 1:15 t "Trunk x velocity" w l lt 1 lc rgb "blue",\
"YDOTS.dat" u 1:16 t "Trunk z velocity" w l lt 1 lc rgb "green",\
"YDOTS.dat" u 1:17 t "Trunk y velocity" w l lt 1,\
"YDOTS.dat" u 1:18 t "Trunk x velocity" w l lt 1 lc rgb "blue",\
"YDOTS.dat" u 1:19 t "Trunk z velocity" w l lt 1 lc rgb "green"
