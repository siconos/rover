set xrange[0:50]
set yrange[0:50]
set xlabel "Time [s]"
set ylabel "Pvalue"
plot\
"PVALUE.dat" u 1:2 t "Pvalue x" w l lt 1,\
"PVALUE.dat" u 1:3 t "Pvalue y" w l lt 1,\
"PVALUE.dat" u 1:4 t "Pvalue z" w l lt 1
