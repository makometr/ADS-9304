import sys
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import math
import numpy as num
 
file = sys.argv[1]

 
fs = file + ".txt"
 
f = open(fs, 'r')

x, y = [0], [0]
l = 0
 
for l in f:
    row = l.split()
    x.append(float(row[0]))
    y.append(float(row[1]))
 
 
f.close()
 
fig, ax1 = plt.subplots(
    nrows=1, ncols=1,
    figsize=(12, 12)
)
 
t = num.linspace(0.1, max(x))
a = num.log(t+1)/num.log(2)
 
x.pop(0)
y.pop(0)
ax1.plot(x, y, label = 'Количество вызовов операции')
ax1.plot(t, a, label  = 'log2 N')
 
ax1.grid(which='major',
         color = 'k')
 
ax1.minorticks_on()
 
ax1.grid(which='minor',
         color = 'gray',
         linestyle = ':')
 
ax1.legend()
 
ax1.set_xlabel('Количество элементов в дереве')
 
if(file == "resAdd"):
    ax1.set_ylabel('Количество операций для вставки')
if(file == "resDelete"):
    ax1.set_ylabel('Количество операций для удаления')
if(file == "timeDelete"):
    ax1.set_ylabel('Время удаления, мс')
if(file == "timeAdd"):
    ax1.set_ylabel('Время вставки, мс')        
fig.set_figwidth(15)
fig.set_figheight(10)
 
plt.title("Худший случай")
plt.show()
