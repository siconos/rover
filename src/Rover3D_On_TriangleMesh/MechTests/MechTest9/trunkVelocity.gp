set termoption dash
set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "Trunk's Velocity [m/sec]"
set arrow from 50,-100 to 50,45 lw 0.5 lt 2 lc 1 nohead
set arrow from 100,-100 to 100,45 lw 0.5 lt 2 lc 1 nohead
set arrow from 150,-100 to 150,45 lw 0.5 lt 2 lc 1 nohead
plot\
"VELOCITY.dat" u 1:9 t "Trunk y velocity" w l lt 1,\
"VELOCITY.dat" u 1:8 t "Trunk x velocity" w l lt 1 lc rgb "blue",\
"VELOCITY.dat" u 1:10 t "Trunk z velocity" w l lt 1 lc rgb "green"

