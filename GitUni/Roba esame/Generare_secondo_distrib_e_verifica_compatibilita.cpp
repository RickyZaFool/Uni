#include <iostream>
#include <fstream>
#include <cmath>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TApplication.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <vector>
#include <TMath.h>
#include <Math/Minimizer.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <TCanvas.h>

using namespace std;

int main(){
  TApplication app("app",0,0);
  TRandom3 rnd;
  rnd.SetSeed(123456789);

  double x0=10;
  double err=2;
  double sigma=2;

  TH1D h("exp","isto",50,0,0);

  for(int i=0;i<1001;i++){
    double xprimo=rnd.Gaus(x0,sigma);
    double x=xprimo+2*(rnd.Rndm()-0.5)*err;
    h.Fill(x);
    }
  h.Draw();
  TF1 f("f","[0]*TMath::Gaus(x,[1],[2],1)",0,20);
  f.SetParameter(0,1);
  f.SetParameter(1,x0);
  f.SetParameter(2,sigma);

  h.Fit("f","L");
  double p=1-f.GetProb();
  cout<<"p_value vale "<<p<<endl;
  
  if(p>0.5){
    cout<<"la nostra distrib è una gaussiana"<<endl;
  }
  else { 
      cout<<"i dati non seguono una distrib gaussiana"<<endl;
  }
  app.Run(true);
  return 0;
}
