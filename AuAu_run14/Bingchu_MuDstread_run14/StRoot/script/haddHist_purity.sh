#!/bin/bash
date

source $ROOTSYS/bin/thisroot.sh

if [ $# -lt 2 ]; then
    echo "not enough arguements"
    echo "./haddHist_purity.sh <outName> <mergefile>"
	exit
fi

path=/star/data01/pwg/yjzhou19/run14_MuDstread_Yj/script

if [ ! -d ${dir}/out/out_$1_$2 ]; then
  echo "no input"
  exit
fi

ifile=`find ${path}/out/out_$1_$2/ -name "*purity.root" | wc -l`
if [ $ifile -gt 0 ]; then
   echo "found $ifile purity files"
   hadd -f ${path}/out/out_$1_$2/hist_ht_20190402.root `find ${path}/out/out_$1_$2/ -name "*purity.root"`
fi

