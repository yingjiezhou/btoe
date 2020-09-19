#!/bin/bash
date
output_dir=/star/data01/pwg/xiao00/Fast_simulation

star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/D0.list",typeID=421  #D0
star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/D0bar.list",typeID=-421 #D0bar
star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/Dplus.list",typeID=411 #Dplus
star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/Dminus.list",typeID=-411 #Dminus

star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/Ds_plus.list",typeID=431 #Ds_plus
star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/Ds_minus.list",typeID=-431 #Ds_minus
star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/Lc_plus.list",typeID=4122 #Lc_plus
star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/Lc_minus.list",typeID=-4122 #Lc_minus

star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/B0.list",typeID=511  #B0
star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/B0bar.list",typeID=-511 #D0bar
star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/Bplus.list",typeID=521 #Dplus
star-submit-template -template submit.xml -entities filelist="/star/u/xiao00/Run14_Analysis/FastSim/Ana/Bminus.list",typeID=-521 #Dminus
