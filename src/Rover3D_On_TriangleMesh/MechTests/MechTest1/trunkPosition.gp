set xlabel "Distance [m]"
set ylabel "Distance [m]"
set zlabel "Distance [m]"
splot\
"TRUNKPOS.dat" u 2:4:3 t "Trunk position" w l