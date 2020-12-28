import sys
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import math
import numpy as np

file = sys.argv[1]

fs = file

f = open(fs, 'r')

x, y = [0], [0]
l = 0

m,n = 0,0

p = 0

num = 10

for l in f:
    row = l.split()
    m += float(row[0])
    n += float(row[1])
    x.append(float(row[0]))
    y.append(float(row[1]))


f.close()

fig, ax1 = plt.subplots(
    nrows = 1, ncols = 1,
    figsize = (12, 12)
)

xmax = math.sqrt(y[len(y) - 1])

t = np.linspace(0.1, max(x))
j = np.linspace(0.1, max(x))

a = np.log2(t) * t

v = t ** 2

o = j*3

x.pop(0)
y.pop(0)

ax1.plot(x, y, label = 'Затраченное время')
ax1.plot(t, a, label  = 'N logN')
ax1.plot(j, o, label = '3*N')
ax1.plot()


ax1.grid(which = 'major',
         color = 'k')

ax1.minorticks_on()

ax1.grid(which = 'minor',
         color = 'gray',
         linestyle = ':')

ax1.legend()

ax1.set_xlabel('Количество элементов')
ax1.set_ylabel('Затраченное время, мкс')  



plt.title("Лучший случай")
plt.show() 