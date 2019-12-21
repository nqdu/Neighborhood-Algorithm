import numpy as np 
from numpy.random import rand
import matplotlib.pyplot as plt

n = 1000
x = -100 + 200*rand(n)
y = -100 + 200*rand(n)

with open('input/data.in','w') as f:
    f.write('%d\n'%n)
    for i in range(n):
        f.write('%f %f\n'%(x[i],y[i]))

plt.scatter(x,y,s=10)
plt.show()