import os
import sys

path = sys.argv[1]

f = open("myList.list","w+")

for fi in os.listdir(path):
    f.write(path+fi+"\n")
