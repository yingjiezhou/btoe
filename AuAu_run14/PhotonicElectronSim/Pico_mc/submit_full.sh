#!/bin/bash
date
srun=$1
nrun=$2
submitter=$3
path=$PWD
star-submit-template -template submit_full.xml -entities startNRuns=${srun},nRuns=${nrun},base=${path},submitter=${submitter}
#Fix privileges for report, log, etc.
find ./ -maxdepth 1 -user $USER -exec chgrp rhstar {} \;
find ./ -maxdepth 1 -user $USER -exec chmod g+rw {} \;
#
#find ./log/ -user $USER -exec chgrp rhstar {} \;
#find ./log/ -user $USER -exec chmod g+rw {} \;
