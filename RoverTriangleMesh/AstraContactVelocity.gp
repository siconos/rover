set termoption dash
#set xrange[0:50]
#set yrange[0:50]
set term pdf size 5in,6in 
extension= ".pdf"
#set term tikz standalone color solid size 5in,3in
#set term tikz standalone monochrome  size 5in,5in font '\large\sf' 
#extension=".tex"

tmin=5
tmax=250
xmin=-30
xmax=15
qmin=0.5
qmax=1.2


t1=50
t2=100
t3=138.61
t4=180
t5=200

torque_max=11000

set xlabel "Time [s]"
set ylabel "Trunk's Velocity [m/sec]"

set output "Velocity-contact".extension


resultfile="VELOCITY.dat"


basheight = 0.25
heightoff = 0.11
winratio = 1.0
winheight = basheight*winratio
hoffset = 0.05
set lmargin 8 
set bmargin 0
set tmargin 0

set size 1.0 , 1.0

set xzeroaxis
set format x ""
unset xlabel
set multiplot
set label 1 "\$t_1\$" at first t1-10, first torque_max+1000  
set label 2 "\$t_2\$" at first t2-10, first torque_max+1000 
set label 3 "\$t_3\$" at first t3-10, first torque_max +1000  
set label 4 "\$t_4\$" at first t4-10, first torque_max+1000  
set label 5 "\$t_5\$" at first t5-10, first torque_max +1000  

set size winratio-0.1,1.0*winheight
#set ytics -1.0,0.5,1.
set yrange [xmin:xmax]
set xrange [tmin:tmax]
set origin hoffset,(winheight+0.10)+heightoff
set ylabel "Applied torque (N.m)"


# set arrow 1 from t1,0 to t1,torque_max lw 0.5 lt 2 lc 1 nohead
# set arrow 2 from t2,0 to t2,torque_max lw 0.5 lt 2 lc 1 nohead
# set arrow 3 from t3,0 to t3,torque_max lw 0.5 lt 2 lc 1 nohead
# set arrow 4 from t4,0 to t4,torque_max lw 0.5 lt 2 lc 1 nohead
# set arrow 5 from t5,0 to t5,torque_max lw 0.5 lt 2 lc 1 nohead


set auto
plot "YDOTS.dat"  using 1:2  notitle w lines

# unset arrow 1
# unset arrow 2
# unset arrow 3
# unset arrow 4
# unset arrow 5

unset label 1
unset label 2
unset label 3
unset label 4
unset label 5

set size winratio-0.1,2*winheight
set origin hoffset,(winheight+0.05)*1.0+heightoff

set yrange [xmin:xmax]
set xrange [tmin:tmax]
set ylabel " \$\\dot q_1\$. Trunk x-velocity(m/s)"
set arrow 1 from t1,xmin to t1,xmax lw 0.5 lt 2 lc 1 nohead
set arrow 2 from t2,xmin to t2,xmax lw 0.5 lt 2 lc 1 nohead
set arrow 3 from t3,xmin to t3,xmax lw 0.5 lt 2 lc 1 nohead
set arrow 4 from t4,xmin to t4,xmax lw 0.5 lt 2 lc 1 nohead
set arrow 5 from t5,xmin to t5,xmax lw 0.5 lt 2 lc 1 nohead

#set arrow from 0,1 to 100,1 nohead ls 3
#plot resultfile  using 1:8  notitle w lines
unset arrow 1
unset arrow 2
unset arrow 3
unset arrow 4
unset arrow 5
set size winratio-0.1,1*winheight
set bmargin 0
set format
set xtics border
set xlabel "\$t\$ (time s)"
set ylabel "\$C \$ "
set origin hoffset,winheight*0.0+heightoff
set arrow 1 from t1,qmin to t1,qmax lw 0.5 lt 2 lc 1 nohead
set arrow 2 from t2,qmin to t2,qmax lw 0.5 lt 2 lc 1 nohead
set arrow 3 from t3,qmin to t3,qmax lw 0.5 lt 2 lc 1 nohead
set arrow 4 from t4,qmin to t4,qmax lw 0.5 lt 2 lc 1 nohead
set arrow 5 from t5,qmin to t5,qmax lw 0.5 lt 2 lc 1 nohead
set ylabel "\$q_1\$  Trunk x-position (m)"

set yrange [qmin:qmax]
plot "TUNKPOS.dat"  using 1:3 notitle w lines
unset arrow 1
unset arrow 2
unset arrow 3
unset arrow 4
unset arrow 5
unset multiplot