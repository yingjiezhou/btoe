#!/usr/local/bin/perl

$outfile = "St_ehcorrelation_Run$ARGV[0].xml";
@dir = qx{pwd};

print "$outfile \n";

open(MAKE_FILE, "> $outfile");

print MAKE_FILE "<?xml version=\"1.0\" encoding=\"utf-8\" ?> \n";
print MAKE_FILE "<job fileListSyntax=\"xrootd\" maxFilesPerProcess=\"10\" filesPerHour=\"20\"> \n";
print MAKE_FILE " <command> \n";
#print MAKE_FILE "	cd /star/u/sshingo/ucla/2008/09/18/toCVS/ \n";
print MAKE_FILE "	cd @dir\n";
print MAKE_FILE "	cd ../ \n";
#print MAKE_FILE "	/star/u/starlib/ROOT/xrootd/bin/preStageFileList \$\{FILELIST\}  \n";
print MAKE_FILE "	        root4star -q -b St_ehcorrelation.C\\(0,\$INPUTFILECOUNT,\\\"\$FILELIST\\\",\\\"\$SCRATCH\\\",\\\"$ARGV[0]_\$JOBID\\\"\\)  \n";
print MAKE_FILE "	        root4star -q -b St_ehcorrelation.C\\(10,\$INPUTFILECOUNT,\\\"\$FILELIST\\\",\\\"\$SCRATCH\\\",\\\"$ARGV[0]_\$JOBID\\\"\\)  \n";
print MAKE_FILE "		rm core* \n";
print MAKE_FILE "		cd Sublist/ \n";
print MAKE_FILE "		rm sched*\$JOBID* \n";
print MAKE_FILE "	</command> \n";
print MAKE_FILE "	<input URL=\"catalog:star.bnl.gov?collision=pp200,production=P06ie,trgsetupname=ppProduction||ppProductionLong||pp2006MinBias||ppProductionTrans,tpc=1,emc=1,runnumber=$ARGV[0],filename~physics,filetype=daq_reco_mudst,runtype=physics,available=1,sanity=1\" nFiles=\"all\" /> \n";	
print MAKE_FILE "	<stdout URL=\"file:/dev/null\" /> \n";
print MAKE_FILE "	<stderr URL=\"file:/dev/null\" /> \n";
#print MAKE_FILE "	<stdout URL=\"file:/star/u/sshingo/ucla/2008/08/18/toCVS/\$JOBID.out\" /> \n";
#print MAKE_FILE "	<stderr URL=\"file:/star/u/sshingo/ucla/2008/09/18/toCVS/logs/\$JOBID.err\" /> \n";
print MAKE_FILE "	<output fromScratch=\"*histogram.root\" toURL=\"file:/star/u/sshingo/ucla/2008/09/18/toCVS/\" /> \n";
# need change toURL to your deirectry
print MAKE_FILE "	</job> \n"; 
