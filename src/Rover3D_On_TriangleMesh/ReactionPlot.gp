set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "Forces [N]"
plot\
"LAMBDAS.dat" u 1:($2+$5+$8+$11+$14+$17) t "Sum of the reaction forces for all the wheels" w l
#"LAMBDAS.dat" u 1:($8+$11) t "Wheel 2" w l,\
#"LAMBDAS.dat" u 1:($14+$17) t "Wheel 3" w l
