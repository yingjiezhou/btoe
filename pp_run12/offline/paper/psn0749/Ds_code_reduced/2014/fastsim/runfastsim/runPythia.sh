#!/bin/bash
mkdir production
for((i=0; i<=8;i++))
do
	let num=${i}+1
#echo ${num}
		nohup root -b -l -q Pythia_toyMcDs_right_Eff.C+\(\"./production/DsSimu_Pythia6_run14_ForEff_${i}.root\",1000000,${i},${num}\) >  ${i}.log &
sleep 2	
done
