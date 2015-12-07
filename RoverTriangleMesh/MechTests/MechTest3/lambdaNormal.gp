set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel " sum of Reaction Forces (lambda normal) [N]"
plot\
"LAMBDAS.dat" u 1:2 t "lambda normal for wheel FL" w l lt 1,\
"LAMBDAS.dat" u 1:5 t "lambda normal for wheel FR" w l lt 1,\
"LAMBDAS.dat" u 1:8 t "lambda normal for wheel ML" w l lt 1,\
"LAMBDAS.dat" u 1:11 t "lambda normal for wheel BL" w l lt 1,\
"LAMBDAS.dat" u 1:14 t "lambda normal for wheel MR" w l lt 1,\
"LAMBDAS.dat" u 1:17 t "lambda normal for wheel BR" w l lt 1
