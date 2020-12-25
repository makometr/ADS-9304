import matplotlib.pyplot as plt
import numpy as np
import random
import math as mt

x = np.arange(0.0001, 1e5, 0.01)

f = open("research.txt", 'r')

num = 0
secs = []
oper = []

for line in f:
    s = line.split()
    secs.append(float(s[0]))
    oper.append(float(s[1]))

t = np.linspace(0.001, max(secs))

y = np.log2(x)

plt.plot(x, y, "red")
plt.plot(secs, oper, "b")

plt.xlabel("Число узлов")
plt.ylabel("Количество операций")
plt.title("Вставка")
plt.grid()
plt.show()