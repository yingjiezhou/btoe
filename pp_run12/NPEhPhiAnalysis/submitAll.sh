#!/bin/bash
date

if [ $# -lt 1 ]; then
echo "not enough arguements"
echo "./submitAll.sh <outName>"
exit
fi

if [ ! -d out ]; then
mkdir out
fi
if [ ! -d log ]; then
mkdir log
fi

dir=$(pwd)
ver=$1
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


if [ ! -d $dir/submit/$1 ]; then
mkdir $dir/submit/$1
fi
cp $dir/pp200.xml $dir/submit/$1/.
cd $dir/submit/$1/
if [ ! -d ${dir}/out/out_$1 ]; then
mkdir ${dir}/out/out_$1
fi
if [ ! -d ${dir}/log/log_$1 ]; then
mkdir ${dir}/log/log_$1
fi

star-submit-template -template pp200.xml -entities path=${dir},ver=$1,run=$runId,listOfFiles=femtoDst.list
