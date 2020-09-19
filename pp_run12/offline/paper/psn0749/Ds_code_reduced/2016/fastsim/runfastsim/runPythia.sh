#!/bin/bash
mkdir production
for((i=0; i<=8;i++))
do
	let num=${i}+1
#echo ${num}
		nohup root -b -l -q Pythia_toyMcDs_right_Combined_Eff.C+\(\"./production/DsSimu_Pythia6_Combined_run16_Eff_${i}.root\",1000000,${i},${num}\) >  ${i}.log &
sleep 4	
done
