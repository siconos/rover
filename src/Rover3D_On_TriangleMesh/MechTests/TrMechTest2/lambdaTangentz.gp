set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel " sum of Reaction Forces (lambda normal) [N]"
plot\
"LAMBDAS.dat" u 1:$4 t "lambda normal for wheel FL" w l\
"LAMBDAS.dat" u 1:$7 t "lambda normal for wheel FR" w l\
"LAMBDAS.dat" u 1:$10 t "lambda normal for wheel ML" w l\
"LAMBDAS.dat" u 1:$13 t "lambda normal for wheel BL" w l\
"LAMBDAS.dat" u 1:$16 t "lambda normal for wheel MR" w l\
"LAMBDAS.dat" u 1:$19 t "lambda normal for wheel BR" w l
