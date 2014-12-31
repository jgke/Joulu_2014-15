#!/usr/bin/gnuplot
reset
set terminal png
set xlabel "n"
set ylabel "time (milliseconds)"
set title "Qtree map"

set logscale x
f(x) = a*x+abs(b)
fit [1:] f(x) 'qtree-map.dat' via a,b
plot [1:] f(x) title "time taken", \
 'qtree-map.dat' with points title ""
