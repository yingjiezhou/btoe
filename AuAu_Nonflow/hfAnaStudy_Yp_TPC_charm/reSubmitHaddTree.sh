#!/bin/bash
date

dir=$(pwd)
echo $dir

declare -a aPtHatBin=(1 100)
nPtHatBin=$((${#aPtHatBin[@]} - 1))
 #
for randomSeed in {1..1000}
do 
 for ((i=0; i<${nPtHatBin}; i++))
 do
   dPtHatMin=${aPtHatBin[i]}
   dPtHatMax=${aPtHatBin[i+1]}
   #rm script/genB_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.sh
   #sed s/randomSeed/${randomSeed}/ genB.sh | sed s/pTHatMin/${dPtHatMin}/ | sed s/pTHatMax/${dPtHatMax}/ > script/genB_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.sh
   #chmod +x script/genB_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.sh
   if [ -e output/NpeBHcorr_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}_hist.root ];
   then 
       fsize=$(ls -l output/NpeBHcorr_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}_hist.root | awk '{print $5}')
       if [ "$fsize" -lt "200000" ];
       then
           echo "deleting root file: ${randomSeed}"
           rm output/NpeBHcorr_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}_hist.root
   #cp run.con script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   #echo "Executable       = script/genB_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.sh">>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   #echo "Output           = log/run_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.out">>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   #echo "Error            = log/run_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.err">>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   #echo "Log              = log/run_r${randomSeed}pT${dPtHatMin}_${dPtHatMax}.olog">>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   #echo  "Queue" >>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   #echo  "     " >>script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   #condor_submit  script/runHaddAllTree_${randomSeed}pT${dPtHatMin}_${dPtHatMax}.con
   fi
   fi
 done
done 
