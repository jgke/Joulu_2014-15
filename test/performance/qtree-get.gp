#!/usr/bin/gnuplot
reset
set terminal png
set xlabel "n"
set ylabel "time (milliseconds)"
set title "Qtree get"

set logscale x
f(x) = a*log(x)+abs(b)
fit [1:] f(x) 'qtree-get.dat' via a,b
plot [1:] f(x) title "time taken", \
 'qtree-get.dat' with points title ""
