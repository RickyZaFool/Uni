{
  ifstream file("outP2b.dat");
  double I,eI,V,eV;
  double gamma = 0.967;
  TGraphErrors gr;
  int i = 0;
  double Ramb = 45.03;
  double Tamb = 25.82+273.15;
  double nu = 3e8/635e-9;
  double T,eT;
  double Vgen;
  while(file>>Vgen>>I>>eI>>V>>eV){
    T = pow(Vgen/(I*Ramb),gamma)*Tamb;
    eT = (gamma/I)*T*eI;
    gr.SetPoint(i,T,V);
    gr.SetPointError(i,eT,eV);
    i++;
  }
  double alpha = V*(exp(5e-11*nu/T)-1);
  cout << "expAlpha = " << alpha << endl;
  TCanvas c1;
  gr.Draw("AP");
  gr.SetMarkerStyle(20);
  TF1 f("f", "[0]*pow(exp([1]*[2]/x)-1,-1)",2800,3500);
  f.SetParameter(0, alpha);
  f.SetParameter(1, 5e-11);
  f.FixParameter(2, nu);
  gr.Fit("f");
  cout <<"Alpha =" << f.GetParameter(0) << " +/- " << f.GetParError(0) << endl ;
  cout << 6.626e-34/1.38e-23 <<endl;
  cout << "h/k =" << f.GetParameter(1) << " +/- " << f.GetParError(1) << endl;
  cout << "Red chi square = " << f.GetChisquare()/f.GetNDF() <<endl;
}
