import os
import sys

rootDir = sys.argv[1]

f = open("ee_sst.list","a+")


for dirName, subdirList, fileList in os.walk(rootDir):
    #print('Found directory: %s' % dirName) 
    for fname in fileList:
        if fname.endswith('MuDst.root'):
            print('%s' % dirName+"/"+fname)
            f.write(dirName+"/"+fname+"\n") 

