rm -r LocalLibraries.package
rm LocalLibraries.zip
#/common/star/star64/packages/scripts/dev/
set workdir=/star/data01/pwg/yjzhou19/Local/Run14_yj
star-submit-template -template submitPicoNpeAnaMaker_small.xml -entities wkd=${workdir}
condor_q
