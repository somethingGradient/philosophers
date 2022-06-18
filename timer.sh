#!/bin/bash

make re && make clean;

START=$(date +%s%N)



if [ -n "$1" ]; then
	valgrind ./philosophers 1;
else
	./philosophers 4 410 200 200;
fi



END=$(date +%s%N)
DIFF=$((($END - $START)/1000000))
SEC=$((($DIFF)/1000))
echo $'\n\n'"$SEC sec $DIFF ms"