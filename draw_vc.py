import numpy as np 
from scipy.spatial import Voronoi,voronoi_plot_2d
import matplotlib.pyplot as plt

fig = plt.figure(1)
for i in range(1,100,5):
	d = np.loadtxt('out_model/'+str(i)+'.dat')
	vc = Voronoi(d[:,:2])
	ax = fig.add_subplot(111)
	ax.set_xlabel('x')
	ax.set_ylabel('y')
	voronoi_plot_2d(vc,ax=ax,show_vertices=False)
	ax.set_xlim([-20,20])
	ax.set_ylim([-20,20])
	ax.scatter([0.0],[0.0],s=3,color='k')
	fig.add_axes(ax)
	#plt.show()
	plt.pause(1)
	fig.clf()