#!/bin/bash

make re && make clean;

START=$(date +%s%N)



if [ -n "$1" ]; then
	valgrind --leak-check=full ./philo 2 600 300 200 0;
else
	./philo 2 600 300 200 2;
fi



END=$(date +%s%N)
DIFF=$((($END - $START)/1000000))
SEC=$((($DIFF)/1000))
echo $'\n\n'"$SEC sec $DIFF ms"