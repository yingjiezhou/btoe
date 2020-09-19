#!/usr/local/bin/perl

$runlist = $ARGV[0];

open(IN, "< $runlist");
@run = <IN>;  
close(IN);
chomp(@run);

$max = 500;

$i = 0;
$n = @run;

#system("mkdir logs");

while($i < $n)
{
    #@busers = `busers`;
    #@jobs = split(/\s+/, $busers[1]);
    #$n_jobs = $jobs[3];

    $n_jobs = qx{condor_q | grep sshingo | wc -l };
    chomp($n_jobs);
    print "n_jobs=$n_jobs\n";
    
    if($n_jobs < $max){
	print "#run = $run[$i]\n";
	system("./make_ehcorrelation_xml.perl $run[$i]");
	#system("./make_St_ehcorrelation_LocalMin_xml.perl $run[$i]");
	system("star-submit St_ehcorrelation_Run$run[$i].xml");
	$i++;
    }else{
	sleep 300;
     }
}
