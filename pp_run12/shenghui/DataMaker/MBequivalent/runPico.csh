#!/bin/csh
cd /star/u/shenghui/shenghui/lbl/Run12/NPE/analysiscode/notecode/HT/RawYield/DataMaker/MBequivalent/
#starver SL12d_embed
starver SL19e

root4star -b <<EOF
.x StRoot/macros/readPicoDst.C("../List/$1.list","out/NPE_EMB_$1_HT.root");
.q
EOF
