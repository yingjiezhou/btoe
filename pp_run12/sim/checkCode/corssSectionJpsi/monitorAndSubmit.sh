#!/bin/bash
i=0
max=$1
offset=6000000

while : #infinite loop
do
  jobs="$(condor_q yjzhou19 | wc -l)" # check how many files are running under my name currently

  if [ $jobs -gt 0 ]; then
    jobs=$(($jobs-8)) # qstat has 2 "junk" lines that aren't jobs, these only show when there are jobs. For non-zero job #, subtract 2
  fi

  #echo $jobs
  if [ $jobs -lt $max ]; then #if less than the number of jobs I want running, submit more
    for j in $(seq 1 $max)
    do
      nseed=$(($i*$max+$j+$offset)) #compute a random seed, offset from 0, using two variables to make sure no repeats
      #echo "nseed: $nseed"
      #rm star_hf_tune_v1.1.cmnd_test #remove old command file with old random seed
      sed -e 's/Random:seed = 0/Random:seed = '"$nseed"'/g' "/star/data01/pwg/yjzhou19/Non-flow/Zach/NPEhCorrelations_v3/star_hf_tune_v1.1.cmnd">>"/star/data01/pwg/yjzhou19/Non-flow/Zach/minBiasTemplates121619/macro/bc_total/starTunes/star_hf_tune_v1.1.cmnd_test$nseed" #use sed to replace the random seed line in the basic tune, keep all else hte same
      sed -e 's/star_hf_tune_v1.1.cmnd_test/star_hf_tune_v1.1.cmnd_test'"$nseed"'/g' "/star/data01/pwg/yjzhou19/Non-flow/Zach/NPEhCorrelations_v3/pythiaZach.xml">>"/star/data01/pwg/yjzhou19/Non-flow/Zach/minBiasTemplates121619/macro/bc_total/XMLfiles/pythiaZach"$nseed".xml" #use sed to replace the change which file tune file is being submitted
      star-submit /star/data01/pwg/yjzhou19/Non-flow/Zach/minBiasTemplates121619/macro/bc_total/XMLfiles/pythiaZach$nseed.xml #acutally submit the job
    done
    i=$(($i+1)) #increment the counter
  fi
  rm -rf *.session.xml
  echo "sleep for 120 m"
  sleep 120m # sleep for x minutes before checking the job list
done
