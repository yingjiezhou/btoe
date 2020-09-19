rm -r LocalLibraries.package
rm LocalLibraries.zip
#/common/star/star64/packages/scripts/dev/
star-submit-template -template submitPicoNpeAnaMaker_small.xml -entities listOfFiles=pico_Run14P16id_good.list #pico.list_0725    #picoList_medium.list  #all5.list #3.list
squeue -u mkelsey
