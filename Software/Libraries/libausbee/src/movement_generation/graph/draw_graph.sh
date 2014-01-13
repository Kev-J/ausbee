#!/bin/sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <mvt-filename>"
    exit
fi

REAL_MVT=$1;
Y_LABEL="Movement"

gnuplot -persist <<PLOT
set xlabel "Time[s]"
set ylabel "$Y_LABEL"

set tics out

plot '$REAL_MVT'  using 1:2 with lines lw 2 title "x", \
     '$REAL_MVT'  using 1:3 with lines lw 2 title "y"
quit
PLOT
