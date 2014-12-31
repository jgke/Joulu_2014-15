#!/usr/bin/gnuplot
reset
set terminal png
set xlabel "n"
set ylabel "time (milliseconds)"
set title "Qtree add"

set logscale x
f(x) = a*log(x)+abs(b)
fit [1:] f(x) 'qtree-add.dat' via a,b
plot [1:] f(x) title "time taken", \
 'qtree-add.dat' with points title ""
