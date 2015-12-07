set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "Lambdas [N]"
plot\
"LAMBDAS.dat" u 1:(abs($3)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(abs($6)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(abs($9)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(abs($12)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(abs($15)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(abs($18)) t "lambda1" w l
