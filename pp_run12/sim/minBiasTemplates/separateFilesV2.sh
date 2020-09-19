#!/bin/bash

#check for argument 1
if [ -z "$1" ]
then
  echo "No argument supplied. Arg 1 = folder name"
  exit 1
fi

i=1
files=`find . -maxdepth 1 -name "*.root" -type f -mmin +60 -size +6100k | wc -l`
echo "Num. Files: $files"
while [ $files -gt 0 ]
do
  mkdir $1_set$i
  find . -maxdepth 1 -name "*.root" -type f -mmin +60 -size +6100k | head -1000 | xargs mv -t $1_set$i
  cd $1_set$i
  hadd pythia_tree_$1_$i.root *.root
  cd ..
  echo "/global/homes/z/zamiller/simu/npehOutput/storageDirectoryPWG/minBiasTemplates111915/$1_set$i/pythia_tree_$1_$i.root" >> Trees_$1.list
  files=`find . -maxdepth 1 -name "*.root" -type f -mmin +60 -size +6100k | wc -l`
  echo "$files Remain"
  i=$[i+1]
done
echo "DONE"
