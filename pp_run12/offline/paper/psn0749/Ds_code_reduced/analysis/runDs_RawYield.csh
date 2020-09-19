#!/bin/csh
 # rm $1
g++ -o $1 $1.C `root-config --libs --cflags`
./$1
