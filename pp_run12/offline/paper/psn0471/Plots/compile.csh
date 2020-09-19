#!/bin/csh -f

root -b << EOM
gSystem->CompileMacro("TGraphAsymmErrorsBracket.cxx", "ko", "libBracket");
EOM

root -b << EOM
gSystem->CompileMacro("Graphic.cxx", "ko", "libGraphic");
.q
EOM
