starver pro
echo $FILELIST
root4star -l -b <<EOF
.L /global/homes/z/zamiller/simu/npehOutput/storageDirectoryPWG/minBiasTemplates111915/readTreeSubmit_C.so
readTree("$FILELIST","/global/homes/z/zamiller/simu/npehOutput/storageDirectoryPWG/minBiasTemplates111915/readTreeOutput/readTreeOut_$JOBID.root") 
.q
EOF
