#!/bin/bash

echo " " > fileInput.dat
for pl in $*
do
	echo $pl >> fileInput.dat
	grep "GM (km^3/s^2)" ephemerides/$pl.txt | awk '{print $4}'>> fileInput.dat
    grep -A3 SOE ephemerides/$pl.txt | tail -2 | sed 's/=/ /g' | awk '{print $2 " "$4" " $6}' >> fileInput.dat
    echo " " >> fileInput.dat
done
