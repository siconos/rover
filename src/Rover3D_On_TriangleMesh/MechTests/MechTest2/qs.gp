set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "Generalized positions"
plot\
"POSITION.dat" u 1:2 t "q1 coordinate" w l lt 1,\
"POSITION.dat" u 1:3 t "q2 coordinate" w l lt 1,\
"POSITION.dat" u 1:4 t "q3 coordinate" w l lt 1
#"POSITION.dat" u 1:5 t "q4 coordinate" w l lt 1,\
#"POSITION.dat" u 1:6 t "q5 coordinate" w l lt 1,\
#"POSITION.dat" u 1:7 t "q6 coordinate" w l lt 1,\
#"POSITION.dat" u 1:8 t "q7 coordinate" w l lt 1,\
#"POSITION.dat" u 1:9 t "q8 coordinate" w l lt 1,\
#"POSITION.dat" u 1:10 t "q9 coordinate" w l lt,\
#"POSITION.dat" u 1:11 t "q10 coordinate" w l lt 1,\
#"POSITION.dat" u 1:12 t "q11 coordinate" w l lt 1,\
#"POSITION.dat" u 1:13 t "q12 coordinate" w l lt 1,\
#"POSITION.dat" u 1:14 t "q13 coordinate" w l lt 1,\
#"POSITION.dat" u 1:15 t "q14 coordinate" w l lt 1,\
#"POSITION.dat" u 1:16 t "q15 coordinate" w l lt 1,\
#"POSITION.dat" u 1:17 t "q16 coordinate" w l lt 1,\
#"POSITION.dat" u 1:18 t "q17 coordinate" w l lt 1,\
#"POSITION.dat" u 1:19 t "q18 coordinate" w l lt 1,\
#"POSITION.dat" u 1:20 t "q19 coordinate" w l lt 1,\
#"POSITION.dat" u 1:21 t "q20 coordinate" w l lt 1,\
#"POSITION.dat" u 1:22 t "q21 coordinate" w l lt 1
