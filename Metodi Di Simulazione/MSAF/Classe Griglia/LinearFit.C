{

  ifstream file("data.dat");

  float p;
  TGraphErrors gr;
  int i = 0;
  while(file>>p){;
    gr.SetPoint(i,i,p);
    i++;
  }
  TCanvas c1;
  gr.Draw("AP");
  gr.SetMarkerStyle(20);
}
