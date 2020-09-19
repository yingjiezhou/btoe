#Central 111333
#phoe 1-pion 702
#phoe 1-gamma 704
#phoe2 706
#pt hard 708
#pt soft 710
#more dp 712
#low dp 714

PHE="../../NPE_MC/Ana/root_yj/DCA_plots_yj_central5_v3_2.root"
PHE_pi="../../NPE_MC/Ana/root_yj/DCA_plots_yj_central5_v3_2_morePion.root"
PHE_gamma="../../NPE_MC/Ana/root_yj/DCA_plots_yj_central5_v3_2_moreGamma.root"
constraint_v2=(0.362 0.304 0.283 0.378125  0.311862  0.22964  0.225388  0.217199  0.176918) #default
constraint_v2_pi=(0.362 0.304 0.283 0.405401  0.319827  0.229526  0.233134  0.226814  0.183715) #more pion
constraint_v2_gamma=(0.362 0.304 0.283 0.497317  0.346233  0.22918  0.255818  0.2512  0.198877) #more gamma

HF="../../NPE_MC/Ana/root_yj/HF_plots_C5_yj.root"
HF_soft="../../NPE_MC/Ana/root_yj/HF_plots_C5_yj_soft.root"
HF_hard="../../NPE_MC/Ana/root_yj/HF_plots_C5_yj_hard.root"
pass=11133333
#echo "First Index: ${constraint_v2[0]}"
#echo "${PHE}"
#echo "${HF}"
#echo "runFit_yj.C\(\"${pass}\",\"${PHE}\",\"${HF}\",\"${constraint_v2}\",0.01\)"
echo "${constraint_v2[*]}"
#root -b -q -l runFit_yj.C\(\"${pass}\",\"${PHE}\",\"${HF}\",\"${constraint_v2[@]}\",0.01\)
root -b -q -l test.C\(\"${constraint_v2[@]}\"\)
