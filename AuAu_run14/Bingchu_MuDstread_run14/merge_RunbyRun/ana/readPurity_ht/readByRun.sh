#!/bin/bash
date

source $ROOTSYS/bin/thisroot.sh
if [ $# -lt 2 ]; then
echo "not enough arguements"
echo "./readByRun.sh <outName> <run>"
exit
fi

path=/star/data01/pwg/yjzhou19/run14_MuDstread_Yj/script

run=$2
if [ ! -d ${path}/out/out_$1_purity ]; then
echo "no input"
exit
fi

ifile=`find ${path}/out/out_$1_purity/ -name "*purity.root" | wc -l`
if [ $ifile -gt 0 ]; then
echo "found $ifile purity files"
#echo ${path}/out/out_$1_purity/st_physics_$run.purity.root
root -l readPurity.C\(\"${path}/out/out_$1_purity/st_physics_$run.purity.root\"\)

fi
