#!/bin/bash

make re && make clean;

START=$(date +%s%N)



if [ -n "$1" ]; then
	leaks --atExit -- ./philo 2 120 21 10 1;
else
	./philo 2 1100 500 500 1;
fi



# END=$(date +%s%N)
# DIFF=$((($END - $START)/1000000))
# SEC=$((($DIFF)/1000))
# echo $'\n\n'"$SEC sec $DIFF ms"