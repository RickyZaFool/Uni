#!/bin/bash

echo " " > fileInput.dat
for pl in $*
do
    #   aggiungere GM
    echo $pl >> fileInput.dat
    grep "GM (" ephemerides/$pl.txt | awk '{print $4}' >> fileInput.dat
#    grep -A3 SOE ephemerides/$pl.txt | tail -2 | sed 's/=/ /g'| awk '{print $2" "$4" "$6}'>> fileInput.dat
    grep -A3 SOE ephemerides/$pl.txt | tail -2 | sed 's/=/ /g;s/X/ /g; s/Y/ /g; s/Z/ /g; s/V/ /g' >> fileInput.dat
    echo " " >> fileInput.dat
done
