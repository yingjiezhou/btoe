#!/bin/bash 

date 

myargs=('ds_data.root' 'BDT')
count=0
for i in $@
do
    myargs[$count]=$i
    let "count+=1"
done

root -l -b -q 'TMVAClassificationApplication_run14.C("'${myargs[0]}'","'${myargs[1]}'")'
