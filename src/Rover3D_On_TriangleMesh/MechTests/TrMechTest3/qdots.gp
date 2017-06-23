set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "Generalized velocities"
plot\
"VELOCITY.dat" u 1:2 t "qdot1 coordinate" w l lt 1,\
"VELOCITY.dat" u 1:3 t "qdot2 coordinate" w l lt 1,\
"VELOCITY.dat" u 1:4 t "qdot3 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:5 t "qdot4 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:6 t "qdot5 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:7 t "qdot6 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:8 t "qdot7 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:9 t "qdot8 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:10 t "qdot9 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:11 t "qdot10 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:12 t "qdot11 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:13 t "qdot12 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:14 t "qdot13 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:15 t "qdot14 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:16 t "qdot15 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:17 t "qdot16 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:18 t "qdot17 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:19 t "qdot18 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:20 t "qdot19 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:21 t "qdot20 coordinate" w l lt 1,\
#"VELOCITY.dat" u 1:22 t "qdot21 coordinate" w l lt 1