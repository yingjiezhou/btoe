#!/bin/bash
date
run=$1
#cd submit/
output_dir=/star/data01/pwg/xiao00/Fast_simulation
Nevent=1e7
while [ $run -le $2 ];
do
    star-submit-template -template submit.xml -entities typeID=421,nevent=${Nevent},runnumber=${run}  #D0
    star-submit-template -template submit.xml -entities typeID=-421,nevent=${Nevent},runnumber=${run} #D0bar
    star-submit-template -template submit.xml -entities typeID=411,nevent=${Nevent},runnumber=${run} #Dplus
    star-submit-template -template submit.xml -entities typeID=-411,nevent=${Nevent},runnumber=${run} #Dminus

    star-submit-template -template submit.xml -entities typeID=431,nevent=${Nevent},runnumber=${run} #Ds plus
    star-submit-template -template submit.xml -entities typeID=-431,nevent=${Nevent},runnumber=${run} #Ds minus
    star-submit-template -template submit.xml -entities typeID=4122,nevent=${Nevent},runnumber=${run} #Lc plus
    star-submit-template -template submit.xml -entities typeID=-4122,nevent=${Nevent},runnumber=${run} #Lc minus


    star-submit-template -template submit.xml -entities typeID=511,nevent=${Nevent},runnumber=${run} #B0
    star-submit-template -template submit.xml -entities typeID=-511,nevent=${Nevent},runnumber=${run} #B0bar
    star-submit-template -template submit.xml -entities typeID=521,nevent=${Nevent},runnumber=${run} #Bplus
    star-submit-template -template submit.xml -entities typeID=-521,nevent=${Nevent},runnumber=${run} #Bminus

    echo ${run}
    let "run+=1";
done
