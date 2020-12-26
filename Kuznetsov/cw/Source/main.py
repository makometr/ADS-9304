import sys
import matplotlib.pyplot as plt
import numpy as np
import random
import math as mt

fname = sys.argv[1]
f = open(fname, 'r')
case = "WORST" if fname=="insertWorst.txt" else \
		"BEST" if fname=="insertBest.txt" else \
		"AVERAGE"
nc = []
ops = []

for line in f:
    s = line.split()
    nc.append(int(s[0]))
    ops.append(int(s[1]))



graphLength = 3/4*2**20
totalcount = 2**20;
jumpLength = 1;
opsAvg = [ops[0]]
ncAvg = [nc[0]]
while jumpLength < totalcount:
	ncc = 0
	opc = 0
	for i in range(jumpLength, 2*jumpLength):
		ncc+=nc[i]
		opc+=ops[i]
	ncAvg.append(ncc/jumpLength)
	opsAvg.append(opc/jumpLength)
	jumpLength *=2

x = np.arange(1, graphLength, 0.1)
fstr = "2log(x)" if case=="WORST" else "log(x)"
lb = 2*np.log2(x) if case=="WORST" else np.log2(x)
plt.plot(ncAvg, opsAvg, "b", label="Aproximated complexity")
plt.plot(x, lb, "red", label=fstr)

plt.xlabel("Nodes count")
plt.ylabel("Operations count")
plt.title(f"Insert, case:{case}")
plt.grid()
plt.legend();
plt.show()