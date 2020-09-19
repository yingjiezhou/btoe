#!/bin/csh

if ( -f log_test ) then
   rm log_test
endif

root4star -b -l << EOF >& log_test
.O2
.x StRoot/macros/makeAnaTreeFromPicoDst.C(1000000,15107008,"/gpfs04/star/temp/OSG/146/15146062/st_physics_15146062_raw_5500002.picoDst.root",false,0,1,0)
.q
EOF
