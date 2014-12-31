#!/usr/bin/gnuplot
load "performance.gp"

set title "Qtree contains"
set logscale x
f(x) = a*log(x)+abs(b)
fit [1:] f(x) 'qtree-contains.dat' via a,b
plot [1:] f(x) title "time taken", \
 'qtree-contains.dat' with points title ""
