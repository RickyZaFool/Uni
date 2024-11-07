from ROOT import *
import math as m

rnd = TRandom3()
rnd.SetSeed(1005062003)

tau1 = 0.1
tau2 = 1.0
f    = 0.3

n    = 10000

h1 = TH1D("h1", "tempi dec", 100, 0, 3.0)
h2 = TH1D("h2", "tempi mis", 100, 0, 3.0)

tacc = 0.01

for i in range(0,n):
	if rnd.Rndm() < f:
		tau = tau1
	else:
		tau = tau2
	t = -tau * m.log(1-rnd.Rndm())
	eps = 1 - m.exp(-t/tacc)
	if rnd.Rndm() < eps:
		h2.Fill(t)
	h1.Fill(t)



h1.Draw()
h2.SetLineColor(kRed)
h2.Draw("SAME")
gApplication.Run(True)

