set xlabel "Position"
set ylabel "Value"
set term png
set output "result.png"

set style line 1 lt 1 lw 1 linecolor rgb "black" pt 5 ps 0.4 
set style line 2 lt 2 lw 1 linecolor rgb "blue" pt 7 ps 0.4 
set style line 3 lt 3 lw 1 linecolor rgb "green" pt 9 ps 0.4 
set style line 4 lt 4 lw 1 linecolor rgb "magenta" pt 11 ps 0.4 


plot "./build/ref.dat" with linespoints linestyle 1 title "Exact Solution",      "./build/uw.dat" with linespoints linestyle 2 title "Upwind",      "./build/lwd.dat" with linespoints linestyle 3 title "Laxwendroff",      "./build/init.dat" with linespoints linestyle 4 title "Initial Condition"
