'''
 Schema per lo sviluppo del metodo di Numerov 
'''
import matplotlib.pyplot as plt
import numpy as np
import math

'''
 La proposta di implementazione e' divisa quattro step
 Step 1 (S1)
 Step 2 (S2)
 Step 3 (S3)
 Step 4 (S4)
 i comandi commentati (con # in prima colonna) indicano un comandi gia' pronti,
 utilizzabile quando le parti precedenti sono completate
'''

'''
  S1: definire il potenziale in funzione della variabile normalizzata xi
'''   
def V(xi):
	v = xi*xi + y*xi*xi*xi*xi
	return v


'''
  S1: calcolo di b a partire dall'energia normalizzata eps, della coordinata
  normalizzata xi e dallo passo h (variabile globale)
'''
def b(eps,xi):
    b = (h*h/12.0)*(2*eps - V(xi))
    return b


'''
  S1/S2: completare la funzione Numerov che riempe i valori di psi(xi) 
         dall'indice n1 all'indice n2 (entrambi compresi)
         Schema:
           - definisco indice j in modo che 1 se n2>n1, -1 se n2<n1 (vedi sign di numpy)
             in questo modo:
               se j =  1 indice i, i+j,i+2*j -> i, i+1, i+2
               se j = -1 indice i, i+j,i+2*j -> i, i-1, i-2
           - fornisco i primi due valori di psi
           - implemento Numerov (ciclo for)
'''
def numerov(n1,n2,eps):
    psi = np.array(xi)*0  # copio xi in psi e lo azzero
    j = np.sign(n2-n1)
    for i in range(n1,n2+j,j):
    	if i == n1:
    		psi[i] = 0
    	elif i == n1+j:
    		psi[i] = 0.01
    	else:
    		psi[i] = (2*psi[i-j]*(1-5*b(eps,xi[i-j]))-psi[i-2*j]*(1+b(eps,xi[i-2*j])))/(1+b(eps,xi[i]))
    return psi



'''
  S3: completare evalDerivative
     - per l'energia eps fornita dall'utente crea soluzione left e right
     - le normalizza a nmatch (si consiglia di normalizzare psir a psil)
     - calcola la differenza (diff) tra le derivate centrate (left e right) in match
'''
def evalDerivative(eps):
    global psir,psil
    psil = numerov(0,nmatch+1,eps)
    psir = numerov(n-1,nmatch-1,eps)
    psir *= (psil[nmatch]/psir[nmatch])
    psil_der = (psil[nmatch+1]+psil[nmatch-1])/(2*h)
    psir_der = (psir[nmatch+1]+psir[nmatch-1])/(2*h)
    diff = psil_der - psir_der
    return diff

''' 
  Metodo di bisezione per trovare l'energia in cui la funzione evalDerivative
  e' nulla. Cioe' l'enegia per cui  la derivata sinistra e destra coincidono 
'''
def findE(emin,emax,tol):
    while (emax-emin>tol):
        emed = (emin+emax)/2
        if evalDerivative(emin)*evalDerivative(emed)<0:
            emax = emed
        else:
            emin = emed
    return (emin+emax)/2;
 
''' 
  Codice principale: l'esecuzione dello script parte da qui
'''
n       = 14000
nmatch  = 10000
y = 0.100
xi      = np.linspace(-7.,7,n)
h       = xi[1]-xi[0]

'''
  S1: verifico Numerov chiamando la funzione da sinistra a destra
  e la disegno
'''
'''
epsilon = 0.5   # o altra energia di stato definito eps = (n+1/2)
psi=numerov(0,n-1,epsilon)
plt.plot(xi,psi)
plt.show()
'''
'''
  S2: come S1 ma verifico che funzioni anche da destra a sinistra
  e la disegno
'''
'''
epsilon = 0.5   # o altra energia di stato definito eps = (n+1/2)
psi=numerov(n-1,0,epsilon)
plt.plot(xi,psi)
plt.show()
'''
'''
  S3:
   - commentare i punti precedenti (a parte le definizioni iniziali del Main code
   - completare evalDerivative 
   - chiamare findE 
   - fare grafico delle due funzioni 
'''

e = findE(0.5,0.65,0.000001)
print("Energy ",e)
print("2epsilon", 2*e)
epsilon = e   # o altra energia di stato definito eps = (n+1/2)
#plt.plot(xi,psil)
#plt.plot(xi,psir)
#plt.show()

for i in range(n-nmatch-1):
	psil[i+nmatch+1]=psir[i+nmatch+1]


plt.plot(xi,psil)

plt.show()
'''
  S4:
   - copiare psr nella parte 'vuota' di psil di modo che psil rappresenti tutta psi(x)
     nell'intervallo dato o, alternativamente, copiarle entrambe in una nuova psi
   - disegnare la funzione d'onda trovata
'''
