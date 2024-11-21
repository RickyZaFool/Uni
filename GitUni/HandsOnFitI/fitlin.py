from   iminuit import Minuit
import numpy as np
import matplotlib.pyplot as plt

def f(x,p):
    return p[1]*x+p[0]

def fcn(par):
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],par))/ey[i])**2
    return val

# Acquisizione dati
x,y,ex,ey = np.loadtxt('pendolo.dat',usecols=(0,1,2,3),unpack=True)

par = np.array([0,4])
m = Minuit(fcn,par)
m.errordef = Minuit.LEAST_SQUARES
m.print_level = 2
m.migrad()

print(m.values[0], m.values[1])
print(m.errors[0], m.errors[1])

print(m.covariance)
#m.draw_mncontour(0,1, cl=[1,2,3] )
#plt.show()
m.draw_mnmatrix(cl=[1,2,3])
plt.show()

## Chiamare Minuit 
## Stampare la matrice di correlazione (correlation)
## Esplorare la funzione draw_mncontour un contour
## Esplorare la funzione draw_mnmatrix per fare la matrice dei contour

