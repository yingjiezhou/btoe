#!/bin/bash

date 

if [ $# -ne 2 ]
then 
    echo -e "\033[31m Please input your filelist, and try a again ! bye. \033[0m"
    exit 1
fi 
filelist=$1
trigger=$2
for ifile in `cat ../$filelist`
do 
daynum=`echo $ifile | awk -F '/' '{print $2}'`
day=`echo ${daynum%.*}`
echo "day num : ${day}  trigger $trigger"
     cp runPico.con runPico_${day}_${trigger}.con

     echo "Arguments        = $day" >> runPico_${day}_${trigger}.con
     echo "Output           = log/runPico_${day}_${trigger}.out">>runPico_${day}_${trigger}.con
     echo "Error            = log/runPico_${day}_${trigger}.err">>runPico_${day}_${trigger}.con
     echo "Log              = log/runPico_${day}_${trigger}.log">>runPico_${day}_${trigger}.con
     echo  "Queue"          >>runPico_${day}_${trigger}.con
     echo  "     "          >>runPico_${day}_${trigger}.con

     condor_submit runPico_${day}_${trigger}.con

     mv runPico_${day}_${trigger}.con script/

done
