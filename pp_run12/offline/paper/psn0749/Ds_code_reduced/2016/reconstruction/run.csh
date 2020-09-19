#!/bin/csh

rm $3

nohup root -b -l -q RunMySelector_list.C\(\"$1\",\"$2\"\) > & $3 &
