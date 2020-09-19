#!/bin/bash
date

source $ROOTSYS/bin/thisroot.sh

if [ $# -lt 2 ]; then
    echo "not enough arguements"
    echo "./haddHistQAByRun.sh <outName> <run>"
	exit
fi

#path=/star/u/huangbc/data01/pico/qa/20151125_v4/prod
path=/star/u/ypwang/disk01/analysisHF/Run14_Analysis/Run14_Analysis/Data_Bingchu/prod
target=$(pwd)

if [ ! -d ${target}/out ]; then
   mkdir ${target}/out
fi

if [ ! -d ${target}/out/out_$1_qa]; then
   mkdir ${target}/out/out_$1_qa
fi

run=$2
if [ ! -d ${path}/out/out_$1/${run} ]; then
   echo "no run $run"
   exit
fi
ifile=`find ${path}/out/out_$1/${run} -name "st*${run}*qa.root" | wc -l`
if [ $ifile -gt 0 ]; then
   echo "run ${run}"
   echo "found $ifile qa files"
   if [ ! -f ${target}/out/out_$1_qa/st_physics_${run}.qa.root ]; then
      if [ ! -f ${target}/out/out_$1_qa/${run}_qa_unfinish ]; then
         touch ${target}/out/out_$1_qa/${run}_qa_unfinish
         hadd -f ${target}/out/out_$1_qa/st_physics_${run}.qa.root `find ${path}/out/out_$1/${run} -name "st*${run}*qa.root"`
         rm -f ${target}/out/out_$1_qa/${run}_qa_unfinish
#rm -f ${path}/out/out_$1/${run}/st*${run}*qa.root
      fi
   else
      if [ ! -f ${target}/out/out_$1_qa/${run}_qa_unfinish ]; then
         touch ${target}/out/out_$1_qa/${run}_qa_unfinish
         hadd -f ${target}/out/out_$1_qa/st_physics_${run}.qa_new.root  ${path}/out/out_$1_qa/st_physics_${run}.qa.root `find ${path}/out/out_$1/${run}  -name "st*${run}*qa.root"`
         mv ${target}/out/out_$1_qa/st_physics_${run}.qa_new.root ${target}/out/out_$1_qa/st_physics_${run}.qa.root
         rm -f ${target}/out/out_$1_qa/${run}_qa_unfinish
#rm -f ${path}/out/out_$1/${run}/st*${run}*qa.root
      fi
   fi
fi
