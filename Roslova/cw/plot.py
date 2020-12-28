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

for l in f:
    row = l.split()
    m += float(row[0])
    n += float(row[1])
    p += 1
    if p % 10 == 0:
        x.append(m / 10)
        y.append(n / 10)


f.close()

fig, ax1 = plt.subplots(
    nrows = 1, ncols = 1,
    figsize = (12, 12)
)

t = np.linspace(0.1, max(x))

a = np.log2(t) * t

v = t ** 2

xmax = math.sqrt(y[len(y) - 1])

nfg = np.linspace(0,xmax)

gfn = nfg * nfg

x.pop(0)
y.pop(0)
ax1.plot(x, y, label = 'Затраченное время')
ax1.plot(t, a, label  = 'N logN')

ax1.plot(nfg, gfn, label = 'N^2 в крайней точке X')


ax1.grid(which = 'major',
         color = 'k')

ax1.minorticks_on()

ax1.grid(which = 'minor',
         color = 'gray',
         linestyle = ':')

ax1.legend()

ax1.set_xlabel('Количество элементов')



plt.title("Лучший случай")
plt.show() 