#!/common/star/star64/opt/star/sl64_gcc482/bin/python
__author__ = "Mustafa Mustafa"
__email__ = "mmustafa@lbl.gov"
""" a script to run runPicoDstMaker.C over a list of files in one job """

import sys
import subprocess
from subprocess import PIPE,Popen


def main():

    inputFilesList = sys.argv[1]
    file = open(inputFilesList,'r')
    listOfFiles = file.readlines()
    file.close()
    listOfFiles[:] = map(str.rstrip,listOfFiles)

    for f in listOfFiles:
        baseName = getBaseName(f)
        run = getRunNumber(f)
        day = getDayNumber(run)

        print run
        print baseName
        outPico = 'Event%s.root'%(baseName)

        command = 'runPicoNpeAnaMaker.C(\"%s\",\"%s\")'%(f,outPico)
        print command


def getBaseName(file):
    return file[file.find('st_'):file.find('pico')-1]

def getRunNumber(baseName):
    idx = baseName.find('_raw')
    if idx > 0:
        return int(baseName[idx-8:idx])
    else:
        return -1

def getDayNumber(runnumber):
    if(runnumber<1e7): return 0

    return int((runnumber%1e6)/1e3)

if __name__ == '__main__':
    main()
