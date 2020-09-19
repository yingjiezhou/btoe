#!/bin/bash
date

if [ $# -lt 2 ]; then
    echo "not enough arguements"
    echo "./submitHaddTotal.sh <outName> <mergefile>"
	exit
fi

dir=$(pwd)
echo $dir
if [ ! -d ${dir}/out/out_$1_$2 ]; then
  echo "no input"
  exit
fi

echo $dir
cp run.con runHaddAll_$1_$2.con
echo "Executable       = haddHist_$2.sh">>runHaddAll_$1_$2.con
echo "Arguments        = $1 $2">>runHaddAll_$1_$2.con
echo "Output           = log/log_$1_purity/run_$2.out">>runHaddAll_$1_$2.con
echo "Error            = log/log_$1_purity/run_$2.err">>runHaddAll_$1_$2.con
echo "Log              = log/log_$1_purity/run_$2.olog">>runHaddAll_$1_$2.con
echo  "Queue" >>runHaddAll_$1_$2.con
echo  "     " >>runHaddAll_$1_$2.con

condor_submit runHaddAll_$1_$2.con
