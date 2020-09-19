rm -r LocalLibraries.package
rm LocalLibraries.zip
#/common/star/star64/packages/scripts/dev/
star-submit-template -template submit_small.xml -entities listOfFiles=piList.list
condor_q
