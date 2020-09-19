#!/bin/bash

#: << 'MYCOMMENT'
#####################
# obtain the difference between the current PicoDst List and produced Pico List
#####################
picoDstList=$1
anaTreeList=$2
copiedanaTreeList=$3
submittedList=$4
logList=$5
outputList=$6
runId=$7
dir=$8
outName=$9

if [ -e $outputList ]; then
  rm -f $outputList
fi
touch $outputList

for picoDst in `cat $picoDstList`
do
   anaTree=`basename ${picoDst/picoDst/anaTree}` #for picoDst
   #anaTree=`basename ${picoDst/MuDst/anaTree}` #for muDst
  del=`grep -l $anaTree $anaTreeList` 
  copiedl=`grep -l $anaTree $copiedanaTreeList` 
  picoName=`basename ${picoDst}`
  logl=`grep -l $picoName $logList` 
#echo "logl = $logl"
  submitl=`grep -l $picoName $submittedList`
#echo "submitl = $submitl"

  #find job in queue
  inQuel=0

#  for dataset in `grep -l ${runId} $dir/submit/${outName}/*.dataset`
#  do
##echo "dataset= $dataset"
#  if [ -f $dataset ]; then
#   sesName=`basename $dataset | cut -d '.' -f 1`
#   picoName=`basename $picoDst | cut -d '.' -f 1`
##echo "picoName=$picoName"
#   listFile=`grep -l "$picoName" $dir/submit/${outName}/${sesName}_*.list`
#   cshFile=`echo "$listFile" | sed 's/list/csh/g'`
#   if [ ${#cshFile} -lt 1 ]; then
#      continue
#   fi
##echo "sesName = $sesName, cshFile = $cshFile"
#   findQue=`grep $cshFile $dir/fileList/${outName}/jobQueue.lis`
#  echo "findQue=$findQue"
#   let "inQuel+=${#findQue}"
#  fi
#  done

#  echo "inQuel = $inQuel"
  #echo "nAnaTree = ${#del}, nCopied = ${#copiedl}"
  #Oct 11, 2016 remove this line to resubmit lost jobs.
  if [ ${#submitl} -gt 0 ] && [ ${inQuel} -gt 0 ]; then
#    echo "jobs is in queue, continue"
    continue
  fi
  if [ ${#del} -lt 1 ] && [ ${#copiedl} -le 0 ]; then
#    echo "add to list"
    echo $picoDst >> $outputList
  else
    anaTreeWithPath=`grep $anaTree $anaTreeList`
    #echo "------------------"
    #echo "anaTree = $anaTree anaTreeList = $anaTreeList"
    #echo "anaTreeWithPath = ${anaTreeWithPath}"
    if [ ${#anaTreeWithPath} -gt 1 ]; then
      size=`ls -l ${anaTreeWithPath} | awk '{print $5}'`
      #echo "size = $size"
      if [ ${size} -lt 10000 ]; then
#        echo "add to list"
        echo $picoDst >> $outputList
      fi
    fi
  fi
done

