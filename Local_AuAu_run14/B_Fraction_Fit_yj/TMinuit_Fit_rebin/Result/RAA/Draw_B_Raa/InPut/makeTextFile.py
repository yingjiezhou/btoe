filenames = ["central.txt","statUp.txt","statDown.txt","sysUp.txt","sysDown.txt"]
pT = []
Rb = []
junk = []
dyU = []
dyD = []
dysU = []
dysD = []

with open("central.txt") as f:
    for line in f:
        x, y = line.split()
        pT.append(x)
        Rb.append(y)

with open("statUp.txt") as f:
    for line in f:
        x, y = line.split()
        junk.append(x)
        dyU.append(y)

with open("statDown.txt") as f:
    for line in f:
        x, y = line.split()
        junk.append(x)
        dyD.append(y)

with open("sysUp.txt") as f:
    for line in f:
        x, y = line.split()
        junk.append(x)
        dysU.append(y)

with open("sysDown.txt") as f:
    for line in f:
        x, y = line.split()
        junk.append(x)
        dysD.append(y)

point = zip(pT, Rb, dyU, dyD, dysU, dysD)
print point

for p in point:
    print p[0] + " " + p[1] + " " + p[2] + " " + p[3] + " " + p[4] + " " + p[5]
