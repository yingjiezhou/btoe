#!/bin/bash
date
run=$1
#cd submit/
output_dir=/star/data01/pwg/yjzhou19/Fast_simulation
Nevent=1e7
while [ $run -le $2 ];
do
    star-submit-template -template submit.xml -entities typeID=421,nevent=${Nevent},runnumber=${run}  #D0
    star-submit-template -template submit.xml -entities typeID=-421,nevent=${Nevent},runnumber=${run} #D0bar
    star-submit-template -template submit.xml -entities typeID=411,nevent=${Nevent},runnumber=${run} #Dplus
    star-submit-template -template submit.xml -entities typeID=-411,nevent=${Nevent},runnumber=${run} #Dminus

    echo ${run}
    let "run+=1";
done
