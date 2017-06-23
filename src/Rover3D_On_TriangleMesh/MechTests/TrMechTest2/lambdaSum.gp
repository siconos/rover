set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "Sum of impulses (lambda normal) [N]"
plot\
"LAMBDAS.dat" u 1:($2+$5+$8+$11+$14+$17) t "Sum of the impulses for all the wheels" w l lt 1
