import sys
import matplotlib.pyplot as plt
import numpy as np

file = sys.argv[1]
f = open(file, 'r')
x, y, z, w, log = [], [], [], [], []

for l in f:
    row = l.split()
    if row != []:
        x.append(float(row[0]))
        y.append(float(row[1]))
        z.append(float(row[2]))
        if(file == "results/res_ta.txt" or file == "results/res_tw.txt"):
            w.append(float(row[3]))
            log.append(float(row[4]))

f.close()

t = np.linspace(0.1, max(x))

fig, ax = plt.subplots(figsize=(12,12))
ax.plot(x, y, label = 'IBST', color = 'red')
ax.plot(x,z, label = 'BST', color = 'blue')
if (file == "results/res_ha.txt" or file == "results/res_hw.txt"):
    ax.plot(t, np.log2(t+1), label = 'log2 N+1', color = 'yellow')
else:
    ax.plot(x, w, label = 'std::map', color = 'green')
    if (file == "results/res_ta.txt"):
        ax.plot(x, log, label = 'log2 N', color = 'k')

ax.grid(which='major',color='k')
ax.minorticks_on()
ax.grid(which='minor',color = 'k',linestyle = ':')

ax.legend()
ax.set_xlabel('Количество узлов в дереве')
if (file == "results/res_ha.txt" or file == "results/res_hw.txt"):
    ax.set_ylabel('Высота дерева')
else:
    ax.set_ylabel('Время поиска, мкc')

fig.set_figwidth(15)
fig.set_figheight(15)

if (file == "results/res_ha.txt" or file == "results/res_ta.txt"):
    plt.title("Средний случай")
else:
    plt.title("Худший случай (для BST)")
plt.show()