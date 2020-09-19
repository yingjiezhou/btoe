#!/bin/bash
date

source $ROOTSYS/bin/thisroot.sh

if [ $# -lt 2 ]; then
    echo "not enough arguements"
    echo "./haddHistPUByRun.sh <outName> <run>"
	exit
fi

#path=/star/u/huangbc/data01/pico/purity/20151125_v4/prod
path=/star/u/ypwang/disk01/analysisHF/Run14_Analysis/Run14_Analysis/Data_Bingchu/prod
target=$(pwd)

if [ ! -d ${target}/out ]; then
   mkdir ${target}/out
fi

if [ ! -d ${target}/out/out_$1_purity]; then
   mkdir ${target}/out/out_$1_purity
fi

run=$2
if [ ! -d ${path}/out/out_$1/${run} ]; then
   echo "no run $run"
   exit
fi
ifile=`find ${path}/out/out_$1/${run} -name "st*${run}*purity.root" | wc -l`
if [ $ifile -gt 0 ]; then
   echo "run ${run}"
   echo "found $ifile purity files"
   if [ ! -f ${target}/out/out_$1_purity/st_physics_${run}.purity.root ]; then
      if [ ! -f ${target}/out/out_$1_purity/${run}_purity_unfinish ]; then
         touch ${target}/out/out_$1_purity/${run}_purity_unfinish
         hadd -f ${target}/out/out_$1_purity/st_physics_${run}.purity.root `find ${path}/out/out_$1/${run} -name "st*${run}*purity.root"`
         rm -f ${target}/out/out_$1_purity/${run}_purity_unfinish
#rm -f ${path}/out/out_$1/${run}/st*${run}*purity.root
      fi
   else
      if [ ! -f ${target}/out/out_$1_purity/${run}_purity_unfinish ]; then
         touch ${target}/out/out_$1_purity/${run}_purity_unfinish
         hadd -f ${target}/out/out_$1_purity/st_physics_${run}.purity_new.root  ${path}/out/out_$1_purity/st_physics_${run}.purity.root `find ${path}/out/out_$1/${run}  -name "st*${run}*purity.root"`
         mv ${target}/out/out_$1_purity/st_physics_${run}.purity_new.root ${target}/out/out_$1_purity/st_physics_${run}.purity.root
         rm -f ${target}/out/out_$1_purity/${run}_purity_unfinish
#rm -f ${path}/out/out_$1/${run}/st*${run}*purity.root
      fi
   fi
fi
