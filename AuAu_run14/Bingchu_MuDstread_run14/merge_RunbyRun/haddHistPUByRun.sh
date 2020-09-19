#!/bin/bash
date

source $ROOTSYS/bin/thisroot.sh

if [ $# -lt 2 ]; then
    echo "not enough arguements"
    echo "./haddHistPUByRun.sh <outName> <run>"
	exit
fi

#path=/star/u/huangbc/data01/pico/qaHad/20151125_v4/prod
path=/star/data01/pwg/yjzhou19/run14_MuDstread_Yj
target=$(pwd)

if [ ! -d ${target}/out ]; then
   mkdir ${target}/out
fi

if [ ! -d ${target}/out/out_$1_qaHad ]; then
   mkdir ${target}/out/out_$1_qaHad
fi

run=$2
if [ ! -d ${path}/out/out_$1/${run} ]; then
   echo "no run $run"
   exit
fi
ifile=`find ${path}/out/out_$1/${run} -name "st*${run}*qaHad.root" | wc -l`
if [ $ifile -gt 0 ]; then
   echo "run ${run}"
   echo "found $ifile qaHad files"
   if [ ! -f ${target}/out/out_$1_qaHad/st_physics_${run}.qaHad.root ]; then
      if [ ! -f ${target}/out/out_$1_qaHad/${run}_qaHad_unfinish ]; then
         touch ${target}/out/out_$1_qaHad/${run}_qaHad_unfinish
         hadd -f ${target}/out/out_$1_qaHad/st_physics_${run}.qaHad.root `find ${path}/out/out_$1/${run} -name "st*${run}*qaHad.root"`
         rm -f ${target}/out/out_$1_qaHad/${run}_qaHad_unfinish
#rm -f ${path}/out/out_$1/${run}/st*${run}*qaHad.root
      fi
   else
      if [ ! -f ${target}/out/out_$1_qaHad/${run}_qaHad_unfinish ]; then
         touch ${target}/out/out_$1_qaHad/${run}_qaHad_unfinish
         hadd -f ${target}/out/out_$1_qaHad/st_physics_${run}.qaHad_new.root  ${path}/out/out_$1_qaHad/st_physics_${run}.qaHad.root `find ${path}/out/out_$1/${run}  -name "st*${run}*qaHad.root"`
         mv ${target}/out/out_$1_qaHad/st_physics_${run}.qaHad_new.root ${target}/out/out_$1_qaHad/st_physics_${run}.qaHad.root
         rm -f ${target}/out/out_$1_qaHad/${run}_qaHad_unfinish
#rm -f ${path}/out/out_$1/${run}/st*${run}*qaHad.root
      fi
   fi
fi
