#!/bin/bash
tcsh
cd /star/data01/pwg/yjzhou19/Non-flow/npeHadronPhiCorr_rcf_bottom
source setup.csh
./NPEHDelPhiCorr randomSeed pTHatMin pTHatMax NpeB.cmnd output/NpeBHcorr C
