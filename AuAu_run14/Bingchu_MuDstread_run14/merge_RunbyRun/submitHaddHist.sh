#!/bin/bash
date

if [ $# -lt 1 ]; then
    echo "not enough arguements"
    echo "./submitHaddHist.sh <outName>"
	exit
fi

if [ ! -d out ]; then
    mkdir out
fi
if [ ! -d log_2 ]; then
    mkdir log_2
fi

dir=$(pwd)
ver=$1
echo $dir
if [ ! -d ${dir}/out/out_$1_purity ]; then
	mkdir ${dir}/out/out_$1_purity
fi
if [ ! -d ${dir}/log_2/log_2_$1_purity ]; then
	mkdir ${dir}/log_2/log_2_$1_purity
fi

echo $dir
cp run.con runHaddAll_$1.con
echo "Executable       = haddHistPUByRun.sh">>runHaddAll_$1.con
#echo "Executable       = readByRun.sh">>runHaddAll_$1.con
#for runId in `cat runNumberList_$1`
#for runId in `cat runnumber_$1`
for runId in `cat runnumber_$1_test`
do
      echo "Arguments        = $1 $runId ">>runHaddAll_$1.con
      echo "Output           = log_2/log_2_$1_purity/run_$runId.out">>runHaddAll_$1.con
      echo "Error            = log_2/log_2_$1_purity/run_$runId.err">>runHaddAll_$1.con
      echo "Log              = log_2/log_2_$1_purity/run_$runId.olog_2">>runHaddAll_$1.con
      echo  "Queue" >>runHaddAll_$1.con
      echo  "     " >>runHaddAll_$1.con
done
   
condor_submit runHaddAll_$1.con
