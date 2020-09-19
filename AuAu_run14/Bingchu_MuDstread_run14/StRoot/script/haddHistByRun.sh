#!/bin/bash
date

source $ROOTSYS/bin/thisroot.sh

if [ $# -lt 2 ]; then
    echo "not enough arguements"
    echo "./haddHistByRun.sh <outName> <run>"
	exit
fi

path=/star/u/ypwang/disk01/analysisHF/Run14_Analysis/Run14_Analysis/Data_Bingchu/prod

if [ ! -d ${path}/out/out_$1_hist ]; then
   mkdir ${path}/out/out_$1_hist
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
   if [ ! -f ${path}/out/out_$1_hist/st_physics_${run}.purity.root ]; then
      if [ ! -f ${path}/out/out_$1_hist/${run}_purity_unfinish ]; then
         touch ${path}/out/out_$1_hist/${run}_purity_unfinish
         hadd -f ${path}/out/out_$1_hist/st_physics_${run}.purity.root `find ${path}/out/out_$1/${run} -name "st*${run}*purity.root"`
         rm -f ${path}/out/out_$1_hist/${run}_purity_unfinish
         #rm -f ${path}/out/out_$1/${run}/st*${run}*purity.root
      fi
   else
      if [ ! -f ${path}/out/out_$1_hist/${run}_purity_unfinish ]; then
         touch ${path}/out/out_$1_hist/${run}_purity_unfinish
         hadd -f ${path}/out/out_$1_hist/st_physics_${run}.purity_new.root  ${path}/out/out_$1_hist/st_physics_${run}.purity.root `find ${path}/out/out_$1/${run}  -name "st*${run}*purity.root"`
         mv ${path}/out/out_$1_hist/st_physics_${run}.purity_new.root ${path}/out/out_$1_hist/st_physics_${run}.purity.root
         rm -f ${path}/out/out_$1_hist/${run}_purity_unfinish
         #rm -f ${path}/out/out_$1/${run}/st*${run}*purity.root
      fi
   fi
fi

ifile=`find out/out_$1/${run} -name "st*${run}*qa.root" | wc -l`
if [ $ifile -gt 0 ]; then
   echo "found $ifile qa files"
   if [ ! -f st_physics_${run}.qa.root ]; then
      if [ ! -f out/out_$1_hist/${run}_qa_unfinish ]; then
         touch out/out_$1_hist/${run}_qa_unfinish
         hadd -f out/out_$1_hist/st_physics_${run}.qa.root `find out/out_$1/${run} -name "st*${run}*qa.root"`
         rm -f out/out_$1_hist/${run}_qa_unfinish
         #rm -f out/out_$1/${run}/st*${run}*qa.root
      fi
   else
      if [ ! -f out/out_$1_hist/${run}_qa_unfinish ]; then
         touch out/out_$1_hist/${run}_qa_unfinish
         hadd -f out/out_$1_hist/st_physics_${run}.qa_new.root  out/out_$1_hist/st_physics_${run}.qa.root `find out/out_$1/${run}/ -name "st*${run}*qa.root"`
         mv out/out_$1_hist/st_physics_${run}.qa_new.root out/out_$1_hist/st_physics_${run}.qa.root
         rm -f out/out_$1_hist/${run}_qa_unfinish
         #rm -f out/out_$1/${run}/st*${run}*qa.root
      fi
   fi
fi
