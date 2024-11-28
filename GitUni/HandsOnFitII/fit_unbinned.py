import ROOT

se = ROOT.TF1("se", "[0]*([3]*TMath::Gaus(x,[1],[2],1)+(1-[3])*(1/[4])*exp(-x/[4]))", 0 , 40)
se.SetParameter(1,15)
se.SetParameter(2,1)
se.SetParameter(3,0.5)
se.SetParameter(4,10)
se.FixParameter(0,1)

tree = ROOT.TTree()
tree.ReadFile("dati.dat","xy/D")

h = ROOT.TH1D("h","h",80,0,40)
tree.UnbinnedFit("se","xy")
tree.Draw("xy>>h")

se.SetParameter(0, h.GetEntries()*h.GetBinWidth(1))
se.Draw("SAME")

ROOT.gApplication.Run(True)
