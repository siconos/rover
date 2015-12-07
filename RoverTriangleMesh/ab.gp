set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "Lambdas [N]"
plot\
"LAMBDAS.dat" u 1:(0.2*$2 - sqrt($4*$4 + $3*$3)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(0.2*$5 - sqrt($6*$6 + $7*$7)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(0.2*$8 - sqrt($9*$9 + $10*$10)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(0.2*$11 - sqrt($12*$12 + $13*$13)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(0.2*$14 - sqrt($15*$15 + $16*$16)) t "lambda1" w l,\
"LAMBDAS.dat" u 1:(0.2*$17 - sqrt($18*$18 + $19*$19)) t "lambda1" w l
