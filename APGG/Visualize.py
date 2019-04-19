from matplotlib import pyplot as plt 
from matplotlib import pyplot as plttest
from matplotlib import style
import numpy as np

spacing = 0.5

plt.subplots_adjust(left=None, bottom=None, right=None, top=None, wspace=spacing, hspace=spacing)

style.use('ggplot')

generation,fitness, coop, defect =  np.loadtxt('Score.csv',
                unpack = True,
                delimiter = ';')



plt.subplot(2,2,1)
plt.plot(generation, fitness)
plt.title('Fitness')
plt.ylabel('Fitness')
plt.xlabel('Generation')


plt.subplot(2,2,2)
plt.plot(generation, defect)
plt.title('Defectors')
plt.ylabel('Defectors')
plt.xlabel('Generation')


plt.subplot(2,2,3)
plt.plot(generation, defect)
plt.title('Cooperators')
plt.ylabel('Cooperators')
plt.xlabel('Generation')


plt.show()
