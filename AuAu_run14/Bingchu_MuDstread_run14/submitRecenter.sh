#!/bin/bash
date

if [ $# -lt 5 ]; then
    echo "not enough arguements"
    echo "./submitRecenter.sh <outName> <mode: 0-mb, 1-ht, 2-mtd> <prod type:0-low and mid, 1-high> <start day> <end day>"
	exit
fi

if [ "$STAR_LEVEL" != "SL16d" ]; then
   echo "wrong library: $STAR_LEVEL, please use SL16d"
   exit
fi

echo "./submitRecenter.sh $1 $2 $3 $4 $5"

prodType=$3
startDay=$4
endDay=$5

# copy src
srcDir=/star/u/huangbc/data01/pico/anaTree/20160607_v5_P16id/prod
scriptDir=/star/u/huangbc/data01/pico/anaTree/20160607_v5_P16id/prod

cp -r $srcDir/StRoot .
cp -r $scriptDir/StRoot/script/AuAu200.xml .
#cp -r $scriptDir/runNumberList_run14AuAu200mb .
#cp -r $scriptDir/recenter_correction.root .

pathTmp=$(pwd)
sed -i "s#${scriptDir}#${pathTmp}#g" AuAu200.xml

#echo $NDHOSTNAME
starver SL16d
cons

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
if [ ! -d ${dir}/out/out_$1 ]; then
	mkdir ${dir}/out/out_$1
fi
if [ ! -d ${dir}/log/log_$1 ]; then
	mkdir ${dir}/log/log_$1
fi

if [ ! -d submit ]; then
   mkdir submit
fi

if [ ! -d submit/$1 ]; then
   mkdir submit/$1
fi

cd submit/$1
 
runNumberFile=

if [ $prodType -eq 0 ]; then
   runNumberFile=runNumber_day_prodLow-Mid_${startDay}-${endDay}_$1_$2
   if [ -f $runNumberFile ]; then
      rm $runNumberFile
   fi
   get_file_list.pl -keys 'runnumber' -cond 'production=P16id,daynumber[]'$startDay-$endDay',collision=auau200,trgsetupname=AuAu_200_production_2014||AuAu_200_production_mid_2014||AuAu_200_production_low_2014,filename~st_physics,filetype=daq_reco_Mudst,storage=local' -limit 0 >& $runNumberFile
fi
if [ $prodType -eq 1 ]; then
   runNumberFile=runNumber_day_prodHigh_${startDay}-${endDay}_$1_$2
   if [ -f $runNumberFile ]; then
      rm $runNumberFile
   fi
   get_file_list.pl -keys 'runnumber' -cond 'production=P16id,daynumber[]'$startDay-$endDay',collision=auau200,trgsetupname=AuAu_200_production_high_2014,filename~st_physics,filetype=daq_reco_Mudst,storage=local' -limit 0 >& $runNumberFile
fi

cp $runNumberFile ../.

for runId in `cat $runNumberFile`
do
   if [ ! -d $dir/submit/$1/$runId ]; then
      mkdir $dir/submit/$1/$runId
   fi
   cp $dir/AuAu200.xml $dir/submit/$1/$runId/.
   cd $dir/submit/$1/$runId/
   if [ ! -d ${dir}/out/out_$1/$runId ]; then
   	mkdir ${dir}/out/out_$1/$runId
   fi
   if [ ! -d ${dir}/log/log_$1/$runId ]; then
   	mkdir ${dir}/log/log_$1/$runId
   fi
   star-submit-template -template AuAu200.xml -entities path=${dir},ver=$1,mode=$2,run=$runId,ptype=$prodType
done
