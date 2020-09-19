rm -r LocalLibraries.package
rm LocalLibraries.zip
#/common/star/star64/packages/scripts/dev/
star-submit-template -template submit_small.xml -entities listOfFiles=myList.list
condor_q
