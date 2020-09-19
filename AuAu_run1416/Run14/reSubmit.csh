input="./CheckFiles/miss_$1.txt"
rm $1_new.condor
job_condor=$1_new.condor
while IFS= read -r line
do  
    echo    "Universe         = vanilla" >> $job_condor
    echo    "Notification     = never" >> $job_condor
    echo    "Executable       = /bin/sh" >> $job_condor
    echo    "Arguments        = \"-c 'exec /gpfs01/star/pwg/mkelsey/Run16/csh/sched$1_$line.csh'\"" >> $job_condor
    echo    "Output           = /gpfs01/star/pwg/mkelsey/Run16/log_tmp/$1_$line.std.log" >> $job_condor
    echo    "Error            = /gpfs01/star/pwg/mkelsey/Run16/log_tmp/$1_$line.std.elog" >> $job_condor
    echo    "request_memory   = 2000" >> $job_condor
    echo    "Log              = /gpfs01/star/pwg/mkelsey/Run16/report/sched$1.condor.log" >> $job_condor
    echo    "Initialdir       = /gpfs01/star/pwg/mkelsey/Run16" >> $job_condor
    echo    "+Job_Type        = \"cas\"" >> $job_condor
    echo    "kill_sig         = SIGINT" >> $job_condor
    echo    "accounting_group = group_star.cas" >> $job_condor
    echo    "PeriodicRemove   = (NumJobStarts >=1 && JobStatus==1) || (JobStatus == 2 && (CurrentTime - JobCurrentStartDate > (54000)) && ((RemoteUserCpu+RemoteSysCpu)/(CurrentTime-JobCurrentStartDate) < 0.10)) || (((CurrentTime - EnteredCurrentStatus) > (2*24*3600)) && JobStatus == 5) || (JobRunCount >= 1 && JobStatus == 1)" >> $job_condor
    echo    "Priority         = +10" >> $job_condor
    echo    "Queue" >> $job_condor
    echo    " " >> $job_condor
done < "$input"
condor_submit $job_condor
