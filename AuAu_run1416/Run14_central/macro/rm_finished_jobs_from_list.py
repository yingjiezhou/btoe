#!/common/star/star64/opt/star/sl64_gcc482/bin/python
__author__ = "Mustafa Mustafa"
__email__ = "mmustafa@lbl.gov"
""" a script to run runPicoDstMaker.C over a list of files in one job """

import sys
import subprocess
from subprocess import PIPE,Popen
INPUTFILE = '/star/u/xyju/pwg/KFParticle/run14charmv1/out/outlist/mylist_low.list'

def main():

    inputFilesList = sys.argv[1]
    file = open(inputFilesList,'r')
    listOfFiles = file.readlines()
    file.close()
    listOfFiles[:] = map(str.rstrip,listOfFiles)

    file2 = open(INPUTFILE,'r')
    listOfFiles2 = file2.readlines()
    file2.close()
    listOfFiles2[:] = map(str.rstrip,listOfFiles2)
    mylist = listOfFiles2[:]
    for f in listOfFiles:
        baseName = getBaseName(f)
        if baseName==-1:
            continue
        for f2 in listOfFiles2:
            if(f2.find(baseName)!=-1):
                mylist.remove(f2)
                break
    with open('mylist_low.list','w') as filehandle:
        filehandle.writelines("%s\n" % mf for mf in mylist)

def getBaseName(file):
    return file[file.find('st_'):file.find('.root')]

if __name__ == '__main__':
    main()
