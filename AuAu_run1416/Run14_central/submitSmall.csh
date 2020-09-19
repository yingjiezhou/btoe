rm -r LocalLibraries.package
rm LocalLibraries.zip
#/common/star/star64/packages/scripts/dev/
star-submit-template -template submitPicoNpeAnaMaker_small.xml -entities listOfFiles=small.list
condor_q
