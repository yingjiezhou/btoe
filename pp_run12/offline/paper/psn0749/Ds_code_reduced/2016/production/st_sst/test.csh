#!/bin/csh
mkdir csh/ err/ list/ log/ production/ report/
rm test.log
nohup root4star -l -b -q readPicoDst.C\(\"test.list\",\"test\"\) >& test.log &