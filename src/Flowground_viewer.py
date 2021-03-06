# Cargo las librerias
import numpy as np
import pandas as pd
from matplotlib import animation
from scipy.interpolate import griddata
import matplotlib.pyplot as plt

# Cargo la malla
geom = pd.read_csv("./RESULTADOS/centers.rep", sep="\t", header=None)
x = geom[0].values
y = geom[1].values
x_aux = np.linspace(min(x), max(x), 50)
y_aux = np.linspace(min(y), max(y), 50)

X,Y = np.meshgrid(x_aux, y_aux)

# Represento la figura
fig = plt.figure()
ims = []
for i in range(0,99):
    path ="./RESULTADOS/results_%i.res" % i
    frame = pd.read_csv(path,header=None)
    P = frame[0].values
    
    Pi = griddata((x, y), P, (X, Y), method='cubic')
    im = plt.pcolormesh(X, Y, Pi)
                            
    ims.append([im])

# Animo las figuras
ani = animation.ArtistAnimation(fig, ims,interval=50, blit=True,
                                repeat_delay=1000)
#plt.show()
ani.save('Flow.mp4', fps = 10)
