set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
#set ylabel "ydot normal"
#set ylabel "ydot tangent x"
set ylabel "ydot tangent z"

#plot normal velocity

#plot\
#"YDOTS.dat" u 1:2 t "lambda normal for wheel FL" w l lt 1,\
#"YDOTS.dat" u 1:5 t "lambda normal for wheel FR" w l lt 1,\
#"YDOTS.dat" u 1:8 t "lambda normal for wheel ML" w l lt 1,\
#"YDOTS.dat" u 1:11 t "lambda normal for wheel BL" w l lt 1,\
#"YDOTS.dat" u 1:14 t "lambda normal for wheel MR" w l lt 1,\
#"YDOTS.dat" u 1:17 t "lambda normal for wheel BR" w l lt 1

#plot tangent x velocity

#plot\
#"YDOTS.dat" u 1:3 t "lambda normal for wheel FL" w l lt 1,\
#"YDOTS.dat" u 1:6 t "lambda normal for wheel FR" w l lt 1,\
#"YDOTS.dat" u 1:9 t "lambda normal for wheel ML" w l lt 1,\
#"YDOTS.dat" u 1:12 t "lambda normal for wheel BL" w l lt 1,\
#"YDOTS.dat" u 1:15 t "lambda normal for wheel MR" w l lt 1,\
#"YDOTS.dat" u 1:18 t "lambda normal for wheel BR" w l lt 1

#plot tangent z velocity

plot\
"YDOTS.dat" u 1:4 t "Trunk y velocity" w l lt 1,\
"YDOTS.dat" u 1:7 t "Trunk x velocity" w l lt 1 lc rgb "blue",\
"YDOTS.dat" u 1:10 t "Trunk z velocity" w l lt 1 lc rgb "green",\
"YDOTS.dat" u 1:13 t "Trunk y velocity" w l lt 1,\
"YDOTS.dat" u 1:16 t "Trunk x velocity" w l lt 1 lc rgb "blue",\
"YDOTS.dat" u 1:19 t "Trunk z velocity" w l lt 1 lc rgb "green"

