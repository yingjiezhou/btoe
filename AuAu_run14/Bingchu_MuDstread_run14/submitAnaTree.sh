#!/bin/bash
date

if [ $# -lt 5 ]; then
  echo "not enough arguements"
  echo "./submitAnaTree.sh <outName> <mode: 0-mb, 1-ht, 2-mtd> <prod type:0-low and mid, 1-high> <start> <end>"
  exit
fi

if [ "$STAR_LEVEL" != "SL16d" ]; then
  echo "wrong library: $STAR_LEVEL, please use SL16d"
  exit
fi

echo "./submitAnaTree.sh $1 $2 $3 $4 $5"

outName=$1
mod=$2
prodType=$3
startDay=$4
endDay=$5
max=30000

# cp src
scriptDir=/star/u/ypwang/disk01/analysisHF/Run14_Analysis/Run14_Analysis/Data_Bingchu/prod

#cp -r $scriptDir/StRoot .
#cp -r $scriptDir/StRoot/script/AuAu200.xml .
#cp -r $scriptDir/runNumberList_run14AuAu200mb .
#cp -r $scriptDir/recenter_correction.root .
#cp -r $scriptDir/runNumberList_run14AuAu200ht_high .
#cp -r $scriptDir/recenter_correction_ht_high.root .

#pathTmp=$(pwd)
#sed -i "s#${scriptDir}#${pathTmp}#g" AuAu200.xml

#echo $NDHOSTNAME
#starver SL16d
#cons

if [ ! -d .sl64_gcc447 ]; then
  ln -s .sl64_gcc482 .sl64_gcc447
fi

if [ ! -d out ]; then
  mkdir out
fi
if [ ! -d log ]; then
  mkdir log
fi

dir=$(pwd)
echo $dir
if [ ! -d ${dir}/out/out_$outName ]; then
  mkdir -p ${dir}/out/out_$outName
fi
if [ ! -d ${dir}/log/log_$outName ]; then
  mkdir -p ${dir}/log/log_$outName
fi

if [ ! -d submit ]; then
  mkdir submit
fi

if [ ! -d submit/$outName ]; then
  mkdir submit/$outName
fi

if [ ! -d fileList/$outName ]; then
  mkdir fileList/$outName
fi

while true; do
   ./generateDayList.sh
   
   if [ -e $dir/fileList/${outName}/sessionXml.lis ]; then
      rm -rf $dir/fileList/${outName}/sessionXml.lis
   fi
   cp $dir/blank $dir/fileList/${outName}/sessionXml.lis
   find $dir/submit/$outName/ -name "*.session.xml" >> $dir/fileList/${outName}/sessionXml.lis
 
   if [ -e $dir/fileList/${outName}/dataset.lis ]; then
      rm -rf $dir/fileList/${outName}/dataset.lis
   fi
   cp $dir/blank $dir/fileList/${outName}/dataset.lis
   find $dir/submit/$outName/ -name "*.dataset" >> $dir/fileList/${outName}/dataset.lis
     
   if [ -e $dir/fileList/${outName}/jobQueue.lis ]; then
      rm -rf $dir/fileList/${outName}/jobQueue.lis
   fi
   cp $dir/blank $dir/fileList/${outName}/jobQueue.lis
   condor_q -global -wide huangbc >> $dir/fileList/${outName}/jobQueue.lis

  nTotal=0
  nAna=0
  for day in `seq ${startDay} 1 ${endDay}`
#for day in `seq 99 1 99`
  do
    if [ $day -gt 0 ] && [ $day -lt 10 ]; then
      dayxxx="00${day}"
    fi
    if [ $day -gt 10 ] && [ $day -lt 100 ]; then
      dayxxx="0${day}"
    fi
    if [ $day -ge 100 ]; then
      dayxxx=${day}
    fi

    echo $dayxxx
    #loop runs 
    for run in `cat $dir/List/day${day}.lis`
    do
      nPico=`ls -1 /gpfs04/star/temp/OSG/${dayxxx}/${run}/ | wc -l`
      let "nTotal+=nPico"
      if [ $nPico -eq 0 ]; then
        echo "can't find picoDst for run $run"
        continue
      fi
      cd $dir

      while :
      do
        jobs="$(condor_q -global huangbc | wc -l)" # check how many files are running under my name currently
        echo "jobs = $jobs"
        if [ $jobs -gt 0 ]; then
          jobs=$(($jobs-6))
        fi

        if [ $jobs -gt $max ]; then
          echo "current number of jobs = $jobs"
          echo "sleep for 30 m"
          date
          sleep 30m # sleep for x minutes before checking the job list
        else
          break;
        fi
      done

      echo "day = $dayxxx run = $run"
#     if [ ! -d $dir/submit/$1/$run ]; then
#        mkdir -p $dir/submit/$1/$run
#      fi
      
      if [ -e $dir/fileList/${outName}/run_current_PicoDst_${run}.lis ]; then
        rm -rf $dir/fileList/${outName}/run_current_PicoDst_${run}.lis
      fi
      cp $dir/blank $dir/fileList/${outName}/run_current_PicoDst_${run}.lis

      if [ ! -e $dir/fileList/${outName}/run_PicoDst_${run}.lis ]; then
         cp $dir/blank $dir/fileList/${outName}/run_PicoDst_${run}.lis
         cp $dir/blank $dir/fileList/${outName}/run_old_PicoDst_${run}.lis
      else 
         cp $dir/fileList/${outName}/run_PicoDst_${run}.lis $dir/fileList/${outName}/run_old_PicoDst_${run}.lis
         cp $dir/blank $dir/fileList/${outName}/run_PicoDst_${run}.lis
      fi

      echo "getting files for run $run"
      find /gpfs04/star/temp/OSG/${dayxxx}/${run}/ -name "*.root" >> $dir/fileList/${outName}/run_current_PicoDst_$run.lis 

      cat $dir/fileList/${outName}/run_current_PicoDst_$run.lis $dir/fileList/${outName}/run_old_PicoDst_${run}.lis | sort | uniq >> $dir/fileList/${outName}/run_PicoDst_${run}.lis

      if [ -e $dir/fileList/${outName}/run_anaTree_${run}.lis ]; then
        rm -rf $dir/fileList/${outName}/run_anaTree_${run}.lis
      fi
      cp $dir/blank $dir/fileList/${outName}/run_anaTree_${run}.lis
      ls -1 $dir/out/out_$1/$run/*.anaTree.root >> $dir/fileList/${outName}/run_anaTree_${run}.lis

      if [ -e $dir/fileList/${outName}/run_log_${run}.lis ]; then
        rm -rf $dir/fileList/${outName}/run_log_${run}.lis
      fi
      cp $dir/blank $dir/fileList/${outName}/run_log_${run}.lis
      ls -1 $dir/log/log_$1/$run/*.root.log >> $dir/fileList/${outName}/run_log_${run}.lis

      if [ -e $dir/fileList/${outName}/run_tobeSubmitted_${run}.lis ]; then
        rm -rf $dir/fileList/${outName}/run_tobeSubmitted_${run}.lis
      fi
      cp $dir/blank $dir/fileList/${outName}/run_tobeSubmitted_${run}.lis
      
      if [ ! -e $dir/fileList/${outName}/run_submitted_${run}.lis ]; then
        cp $dir/blank $dir/fileList/${outName}/run_submitted_${run}.lis
      fi
      
      if [ ! -e $dir/fileList/${outName}/run_transferred_${run}.lis ]; then
        cp $dir/blank $dir/fileList/${outName}/run_transferred_${run}.lis
      fi

      
      echo "#generate filelist to be submitted"
      $dir/diffPicoDstAnaTreeByRun.sh $dir/fileList/${outName}/run_PicoDst_${run}.lis $dir/fileList/${outName}/run_anaTree_${run}.lis $dir/fileList/${outName}/run_transferred_${run}.lis $dir/fileList/${outName}/run_submitted_${run}.lis $dir/fileList/${outName}/run_log_${run}.lis $dir/fileList/${outName}/run_tobeSubmitted_${run}.lis ${run} ${dir} ${outName}

      nLines=`cat $dir/fileList/$outName/run_tobeSubmitted_${run}.lis | wc -l`
      echo "inputs = $nLines"

      if [ ${nLines} -le 0 ]; then
        echo "no input filelist for run $run, skip..."
        continue
      fi

      cp $dir/StRoot/script/AuAu200.xml $dir/submit/$1/
      cd $dir/submit/$1/
      if [ ! -d ${dir}/out/out_$1/$run ]; then
        mkdir -p ${dir}/out/out_$1/$run
      fi
      if [ ! -d ${dir}/log/log_$1/$run ]; then
        mkdir -p ${dir}/log/log_$1/$run
      fi
      star-submit-template -template AuAu200.xml -entities path=${dir},ver=${outName},mode=${mod},run=$run,ptype=$prodType,listOfFiles=$dir/fileList/$outName/run_tobeSubmitted_${run}.lis

      if [ -f temp ]; then
        rm -f temp
      fi
      touch temp
      cat $dir/fileList/$outName/run_submitted_${run}.lis $dir/fileList/$outName/run_tobeSubmitted_${run}.lis | sort | uniq >> temp
      cp temp $dir/fileList/$outName/run_submitted_${run}.lis

    done
    echo "Job submission for day $day finished!"
    date
  done
  echo "All done, go to sleep!"
  date
  sleep 8h
  for day in `seq ${startDay} 1 ${endDay}`
#for day in `seq 99 1 99`
  do
    for run in `cat $dir/List/day${day}.lis`
    do
      nAnaDay=`find ./out/out_$1/${run} -name "*.anaTree.root" | wc -l`
      let "nAna+=nAnaDay"
    done
  done
  echo "nTotal = $nTotal = nAna = $nAna"
  if [ $nTotal -eq $nAna ]; then
    echo "All finished!"
    break
  fi
done
