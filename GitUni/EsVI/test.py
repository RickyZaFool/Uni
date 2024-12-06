#!/usr/bin/python
    
import sys,serial
from dmm import *
from ps  import *
import time

#File di output
file = open('outP2b.dat','w')

i = 20

#Pilotaggio power supply
#Inizializzazione
sopra = serial.Serial('COM6', 9600)
sotto = serial.Serial('COM5', 9600)
instr = psinit("USB0::0x0AAD::0x0135::035375056::INSTR")

pssel(instr,2)
Vfixed = 32
cmd = f'APPLY {Vfixed},0.1'
instr.write(cmd)

pssel(instr,1)
while i < 30:
    #Erogazione di 12 V
    valV = i
    cmd  = f'APPLY {valV},0.1'
    instr.write(cmd)
    #Configurazione seriale
    time.sleep(2)
    #Lettura dal multimetro
    I,ei = dmmread(sopra)
    print(I,ei)
    V,ev = dmmread(sotto)
    print(V,ev)
    
    file.write(str(valV)+'\t')
    file.write(str(I)+'\t')
    file.write(str(ei)+'\t')
    file.write(str(V)+'\t')
    file.write(str(ev)+'\t')
    file.write('\n')
    i = i+1
