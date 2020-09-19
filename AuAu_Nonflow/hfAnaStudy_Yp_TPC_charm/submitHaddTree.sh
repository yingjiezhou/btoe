#!/bin/bash
date

dir=$(pwd)
echo $dir
rm -rf log/*
rm -rf output/*
rm -rf script/*
if [ ! -d ${dir}/output ]; then
    mkdir ${dir}/output
fi
if [ ! -d ${dir}/log ]; then
    mkdir ${dir}/log
fi

if [ ! -d ${dir}/script ]; then
    mkdir ${dir}/script
fi


echo $dir
#declare -a aPtHatBin=(1 100)
declare -a aPtHatBin=(1 5 11 21 36 57 84 100)
nPtHatBin=$((${#aPtHatBin[@]} - 1))
#
#for randomSeed in {1..1000}
#for randomSeed in {4..500}
for randomSeed in {1000..1010}
do
 for ((i=0; i<${nPtHatBin}; i++))
 do
   dPtHatMin=${aPtHatBin[i]}
   dPtHatMax=${aPtHatBin[i+1]}
   rm script/genC_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.sh
   sed s/randomSeed/${randomSeed}/ genC.sh | sed s/pTHatMin/${dPtHatMin}/ | sed s/pTHatMax/${dPtHatMax}/ > script/genC_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.sh
   chmod +x script/genC_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.sh
   if [ ! -e output/NpeCHcorr_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.root ];
   then
   cp run.con script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   echo "Executable       = script/genC_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.sh">>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   echo "Output           = log/run_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.out">>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   echo "Error            = log/run_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.err">>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   echo "Log              = log/run_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.olog">>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   echo  "Queue" >>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   echo  "     " >>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   condor_submit  script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   fi
 done
done
