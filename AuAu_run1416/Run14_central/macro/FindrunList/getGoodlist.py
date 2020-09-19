#!/common/star/star64/opt/star/sl64_gcc482/bin/python
__author__ = "Mustafa Mustafa"
__email__ = "mmustafa@lbl.gov"
""" a script to run runPicoDstMaker.C over a list of files in one job """

import sys
import subprocess
import os
from subprocess import PIPE,Popen

def main():

    inputFilesList = sys.argv[1]
    file = open(inputFilesList,'r')
    listOfFiles = file.readlines()
    file.close()
    listOfFiles[:] = map(str.rstrip,listOfFiles)
    mylist = listOfFiles[:]

    for f in listOfFiles:
        filesize = os.path.getsize(f)
        print filesize
        if(filesize < 282687):
            mylist.remove(f)

    outlist = 'good' + inputFilesList
    with open(outlist,'w') as filehandle:
        filehandle.writelines("%s\n" % mf for mf in mylist)


if __name__ == '__main__':
    main()
