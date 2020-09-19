#!/bin/bash
date
output_dir=/star/data01/pwg/yjzhou19/Fast_simulation

star-submit-template -template submit.xml -entities filelist="/star/u/yjzhou19/analysis/Xiaozhi_Run14/FastSim/Ana/D0.list",typeID=421  #D0
star-submit-template -template submit.xml -entities filelist="/star/u/yjzhou19/analysis/Xiaozhi_Run14/FastSim/Ana/D0bar.list",typeID=-421 #D0bar
star-submit-template -template submit.xml -entities filelist="/star/u/yjzhou19/analysis/Xiaozhi_Run14/FastSim/Ana/Dplus.list",typeID=411 #Dplus
