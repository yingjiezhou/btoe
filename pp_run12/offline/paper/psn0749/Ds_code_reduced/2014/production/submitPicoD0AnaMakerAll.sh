#########################################################################
# File Name: submitPicoD0AnaMaker.sh
# Created Time: Fri 08 May 2015 03:15:35 AM PDT
#########################################################################
#!/bin/tcsh
rm submit.log
nohup star-submit-template -template submitPicoD0AnaMakerAll.xml -entities listOfFiles=$1 > &submit.log &
