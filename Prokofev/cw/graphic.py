import matplotlib.pyplot as plt
import numpy as np
import random

f = open("insert_test.txt", 'r')

num = 0
secs = []
oper = []

for line in f:
    s = line.split()
    secs.append(float(s[0]))
    oper.append(float(s[1]))

#oper = oper[::-1]
#secs = secs[::-1]

totalcount = 2**14

curInd = 1
jumpLength = 2
opsAvg = [oper[0]]
ncAvg = [secs[0]]
while jumpLength < totalcount:
    ncc = 0
    opc = 0
    for i in range(curInd, curInd+jumpLength):
        ncc+=secs[i]
        opc+=oper[i]
    ncAvg.append(ncc/curInd)
    opsAvg.append(opc/curInd)
    curInd=jumpLength
    jumpLength *=2

t = np.linspace(1, max(secs))

y = 4.7*np.log2(t)

plt.plot(t, y, "r", label='O(log2(n))')
plt.plot(ncAvg, opsAvg, "b", label='Практическая оценка')

plt.legend()
plt.xlabel("Число узлов")
plt.ylabel("Высота")
plt.title("Зависимость высоты от числа узлов")
plt.grid()
plt.show()


