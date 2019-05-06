import matplotlib
import matplotlib.pyplot as plt
from matplotlib import style
import numpy as np
import sys


spacing = 0.5

#plt.subplots_adjust(left=None, bottom=None, right=None, top=None, wspace=spacing, hspace=spacing)

style.use('ggplot')

generation,c,d,m,i =  np.loadtxt(sys.argv[1],
                                unpack = True,
                                skiprows = 1,
                                delimiter = ';')


x = generation;
y = np.vstack([c, d, m, i])

labels = ["C", "D", "M", "I"]

fig, ax = plt.subplots()
ax.stackplot(generation, c, d, m, i, labels=labels)
ax.legend(loc='upper left')
plt.show()

fig, ax = plt.subplots()
ax.stackplot(x, y)
plt.show()
