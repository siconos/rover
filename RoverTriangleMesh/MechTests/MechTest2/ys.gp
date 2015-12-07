set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "y"
plot\
"Y.dat" u 1:2 t "Gap function for wheel FL" w l lt 1,\
"Y.dat" u 1:5 t "Gap function for wheel FR" w l lt 1,\
"Y.dat" u 1:8 t "Gap function for wheel ML" w l lt 1,\
"Y.dat" u 1:11 t "Gap function for wheel BL" w l lt 1,\
"Y.dat" u 1:14 t "Gap function for wheel MR" w l lt 1,\
"Y.dat" u 1:17 t "Gap function for wheel BR" w l lt 1