import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import sys

#load data from csv
a,b,c,d,e,f,g,genomeC,genomeM =  np.loadtxt(sys.argv[1],
                                unpack = True,
                                skiprows = 1,
                                delimiter = ';')



# the random data
x = genomeM
y = genomeC


# definitions for the axes
left, width = 0.1, 0.65
bottom, height = 0.1, 0.65
spacing = 0.025


rect_scatter = [left, bottom, width, height]
rect_histx = [left, bottom + height + spacing, width, 0.2]
rect_histy = [left + width + spacing, bottom, 0.2, height]

# start with a rectangular Figure
plt.figure(figsize=(8, 8))

ax_scatter = plt.axes(rect_scatter)
ax_scatter.tick_params(direction='in', top=True, right=True)
ax_histx = plt.axes(rect_histx)
ax_histx.tick_params(direction='in', labelbottom=False)
ax_histy = plt.axes(rect_histy)
ax_histy.tick_params(direction='in', labelleft=False)

# the scatter plot:
ax_scatter.scatter(x, y)

# now determine nice limits by hand:
binwidth = 0.005
lim = np.ceil(np.abs([x, y]).max() / binwidth) * binwidth
ax_scatter.set_xlim((-0.1, 1.1))
ax_scatter.set_ylim((-0.1, 1.1))

bins = np.arange(0, lim + binwidth, binwidth)
ax_histx.hist(x, bins=bins)
ax_histy.hist(y, bins=bins, orientation='horizontal')

ax_histx.set_xlim(ax_scatter.get_xlim())
ax_histy.set_ylim(ax_scatter.get_ylim())

ax_scatter.set_xlabel("probability to punish")
ax_scatter.set_ylabel("probability to cooperate")

plt.show()
