#-0.1*x+0.1*y+0.505 "TAGSDATA.dat" u 13:15:14 t "tire location" w l,\
#set auto
#set xrange[-100:450]
#set yrange[-100:450]
#set zrange[0:30]
set xlabel "distance [m]"
set ylabel "distance [m]"
set zlabel "distance [m]"
set auto
splot\
"TAGSDATA.dat" u 1:3:2 t "FL wheel position" w l,\
"TAGSDATA.dat" u 4:6:5 t "FR wheel position" w l,\
"TAGSDATA.dat" u 10:12:11  t "BL wheel position" w l,\
"TAGSDATA.dat" u 16:18:17  t "BR wheel position" w l,\
"TAGSDATA.dat" u 7:9:8  t "ML wheel position" w l,\
"TAGSDATA.dat" u 13:15:14  t "MR wheel position" w l

