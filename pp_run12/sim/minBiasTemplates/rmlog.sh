#!/bin/bash
while :
do

    echo "sleep for  1.5 d"
    sleep 1.5d
    echo "rm list/ 1440"
    find list/ -type f -mmin +1440 -exec rm {} \;
    echo "rm report/ 1440"
    find report/ -type f -mmin +1440 -exec rm {} \;
    echo "rm err/ 1440"
    find err/ -type f -mmin +1440 -exec rm {} \;
    echo "rm out/ 1440"
    find out/ -type f -mmin +1440 -exec rm {} \;
    echo "rm csh/ 1440"
    find csh/ -type f -mmin +1440 -exec rm {} \;
    echo "rm starTune/ 1440"
    find macro/bc_total/starTunes/ -type f -mmin +1440 -exec rm {} \;
    echo "rm XML/ 1440"
    find macro/bc_total/XMLfiles/ -type f -mmin +1440 -exec rm {} \;
done

