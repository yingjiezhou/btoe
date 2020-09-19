#!/bin/bash

 root -b -l -q 'RunEffSelector_list.C("run.list", "./eff_root/Eff_All.root", 5e8)' 

sleep 3

 ./TMVAClassificationApplication.sh ./eff_root/Eff_All.root BDT 


sleep 3

root -b -l -q 'RunBDTEff_Selector_list.C("run_BDTEff_All.list", "./eff_root/DefaultBDTEff_All.root", 5e8)'

sleep 3

root -b -l -q 'Eff_Final.C ("eff_root/Eff_All.root", "eff_root/DefaultBDTEff_All.root", "eff_root/DefaultBDTEff_All_Final.root" )'
