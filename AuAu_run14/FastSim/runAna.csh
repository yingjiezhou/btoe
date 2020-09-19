#!/bin/tcsh
 echo "D0 analyis start!"
root -l -b -q StRoot/macros/run_StEvtGen_Ana.C'("Ana/D0_test.list","Ana/D0_test.root")';
#root -l -b -q StRoot/macro/run_StEvtGen_Ana.C'("Ana/D0bar.list","Ana/D0bar.root")';
echo "D0 analyis done!"

 exit 0;
 exit 1;

echo "Dplus analyis start!"

root -l -b -q StRoot/macro/run_StEvtGen_Ana.C'("Ana/Dplus.list","Ana/Dplus.root")';
root -l -b -q StRoot/macro/run_StEvtGen_Ana.C'("Ana/Dminus.list","Ana/Dminus.root")';
echo "Dplus analyis done!"



echo "B0 analyis start!"
#root -l -b -q StRoot/macro/run_StEvtGen_Ana.C'("Ana/B0.list","Ana/B0.root")';
#root -l -b -q StRoot/macro/run_StEvtGen_Ana.C'("Ana/B0bar.list","Ana/B0bar.root")';
echo "B0 analyis done!"
echo "Bplus analyis start!"
#root -l -b -q StRoot/macro/run_StEvtGen_Ana.C'("Ana/Bplus.list","Ana/Bplus.root")';
#root -l -b -q StRoot/macro/run_NPE_fast_simulation.C'("Ana/Bminus.list","Ana/Bminus.root")';
echo "Bplus analyis done!"

