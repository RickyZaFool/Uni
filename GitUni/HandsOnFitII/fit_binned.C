void fit_binned(){
	ifstream file("dati.dat");
	double x;
	TH1D *h = new TH1D("h","title",80,0,40);
	while(file >> x){
		h->Fill(x);
	}
	h->SetMarkerStyle(20);
	h->Draw("E");
	TF1 *fe = new TF1("fe", "[0]*([3]*TMath::Gaus(x,[1],[2],1)+(1-[3])*(1/[4])*exp(-x/[4]))", 0 , 40);
	fe->SetParameter(1,15);
	fe->SetParameter(2,1.0);
	fe->SetParameter(4,10);
	fe->SetParameter(3,0.5);
	fe->FixParameter(0,1);
	h->Fit("fe", "0MULTI");
	fe->SetParameter(0, h->GetEntries()*h->GetBinWidth(1));
	fe->Draw("SAME");
}
