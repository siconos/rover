set termoption dash
set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "Wheels' velocities [rad/sec]"
set arrow from 50,-400 to 50,2500 lw 0.5 lt 2 lc 1 nohead
set arrow from 100,-400 to 100,2500 lw 0.5 lt 2 lc 1 nohead
set arrow from 150,-400 to 150,2500 lw 0.5 lt 2 lc 1 nohead
plot\
"VELOCITY.dat" u 1:2 t "FL wheel" w l lt 1 lc rgb "blue",\
"VELOCITY.dat" u 1:3 t "FR wheel" w l lt 1 lc rgb "red",\
"VELOCITY.dat" u 1:4 t "ML wheel" w l lt 1 lc rgb "orange",\
"VELOCITY.dat" u 1:5 t "BL wheel" w l lt 1 lc rgb "green",\
"VELOCITY.dat" u 1:6 t "MR wheel" w l lt 1 lc rgb "yellow",\
"VELOCITY.dat" u 1:7 t "BR wheel" w l lt 1 lc rgb "magenta"