#!/bin/bash
mkdir eff_root

root -b -l -q 'RunEffSelector_list.C("run.list", "./eff_root/Eff_test.root",10000)'

sleep 2

./TMVAClassificationApplication.sh ./eff_root/Eff_test.root BDT


sleep 2

root -b -l -q 'RunBDTEff_Selector_list.C("run_BDTEff_test.list", "./eff_root/DefaultBDTEff_test.root",10000)'

sleep 2

root -b -l -q 'Eff_Final.C ("eff_root/Eff_test.root", "eff_root/DefaultBDTEff_test.root", "eff_root/DefaultBDTEff_test_Final.root" )'
