#set terminal postscript eps enhanced 20 color
#set output "ballonsin.eps"  #set  term X11
set  term X11

!tail -n 100000000 2DRoverResult.dat > result-gp.dat
k=1


plot\
"result-gp.dat" u 2:3 t "Ball position" w l,\
sin(x) #k*x+0.5 w l

