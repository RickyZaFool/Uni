{

  ifstream file("outP1.dat");

  double I,eI,V,eV;
  TGraphErrors gr;
  int i = 0;
  double Rexp;
  double VI;
  double V_I;
  double eV_I;
  while(file>>I>>eI>>V){
    VI = V*I;
    V_I = V/I;
    eV_I = (V*eI)/(I*I);
    gr.SetPoint(i,V_I,VI);
    gr.SetPointError(i,eV_I,eI*V);
    i++;
  }
  Rexp = V/I;
  TCanvas c1;
  gr.Draw("AP");
  gr.SetMarkerStyle(20);
  TF1 f("f","[0]*(pow(pow(x*[2],[1])*[3],4))");
  f.SetParameter(0,2e-14);
  f.SetParameter(1,1);
  f.FixParameter(2,1.0/45.03);
  f.FixParameter(3,273.15+25.82);
  gr.Fit("f");
  cout <<"Alpha =" << f.GetParameter(0) << " +/- " << f.GetParError(0) << endl ;
  cout << "Gamma =" << f.GetParameter(1) << " +/- " << f.GetParError(1) << endl;
  cout << "Red chi square = " << f.GetChisquare()/f.GetNDF() <<endl;

  
}
