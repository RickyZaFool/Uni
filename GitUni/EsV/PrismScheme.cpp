#include <iostream>
#include <cmath>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TApplication.h>

using namespace std;
TApplication app("app",NULL,NULL);
namespace ex{
  double alpha   = M_PI/3;
  double lambda1 = 579.1;
  double lambda2 = 404.7;
  double th0   = 1.5701;
  double th1   = 2.6958;
  double th2   = 2.7904;
  double eth   = 0.0005;
}

void GetAB(double th0, double th1, double th2, double &Atemp, double &Btemp){
  double n1 = sin((th1-th0 + ex::alpha)/2) / sin(ex::alpha /2);
  double n2 = sin((th2-th0 + ex::alpha)/2) / sin(ex::alpha /2);
  Btemp = ((pow(ex::lambda1,2)*pow(ex::lambda2,2))/(pow(ex::lambda1,2) -pow(ex::lambda2,2)))*(n2-n1);
  Atemp = n2-(Btemp/pow(ex::lambda2,2));
}

int main(){
  double g_eth = ex::eth / sqrt(3);
  double A, A0, A1, A2 = 0;
  double B, B0, B1, B2 = 0;
  GetAB(ex::th0, ex::th1, ex::th2, A, B);
  GetAB(ex::th0+g_eth, ex::th1, ex::th2, A0, B0);
  GetAB(ex::th0, ex::th1+g_eth, ex::th2, A1, B1);
  GetAB(ex::th0, ex::th1, ex::th2+g_eth, A2, B2);
  double eA = sqrt(pow(A0-A,2)+pow((A1-A),2)+pow((A2-A),2));
  double eB = sqrt(pow(B0-B,2)+pow((B1-B),2)+pow((B2-B),2));
  cout << "function variance method" << endl ;
  cout << A << " " << eA << "      " << B << " " << eB << endl;
  cout << endl << "*************************************" << endl ;
  
  TRandom3 rnd;
  rnd.SetSeed(time(0));
  TH1D h1 = TH1D("h1", "A", 100, 1.7285, 1.731);
  TH1D h2 = TH1D("h2", "B", 100, 13200, 13700);
  TH2D h3 = TH2D("h3", "A vs B", 100, 1.7285, 1.731, 100, 13200, 13700);
  
  int steps = 10000;
  A = 0;  //hard reset di A e B
  B = 0;
  double Asum = 0;
  double Bsum = 0;
  for(int i=0; i<steps; i++){
  	double theta_1 = rnd.Gaus(ex::th1,g_eth);
  	double theta_2 = rnd.Gaus(ex::th2,g_eth);
  	GetAB(ex::th0, theta_1, theta_2, A, B);
  	Asum += A;
  	Bsum += B;
  	h1.Fill(A);
  	h2.Fill(B);
  	h3.Fill(A,B);
  }
  cout << endl ;
  cout << "Montecarlo method: Gauss" << endl ;
  double Amean = Asum/steps;
  double Bmean = Bsum/steps;
  cout << Amean << "    " << Bmean << endl ;
  TCanvas *c=new TCanvas();
  c->Divide(3,2);
  c->cd(1);
  h1.Draw();
  c->cd(2);
  h2.Draw();
  c->cd(3);
  h3.Draw("colZ");
  cout << h3.GetCorrelationFactor()<< endl;
  //app.Run(true);
  cout << endl << "*************************************" << endl ;
  
  
  TH1D h4 = TH1D("h4", "A", 100, 1.7285, 1.731);
  TH1D h5 = TH1D("h5", "B", 100, 13200, 13700);
  TH2D h6 = TH2D("h6", "A vs B", 100, 1.7285, 1.731, 100, 13200, 13700);
  steps = 1000000;
  A = 0;  //hard reset di A e B
  B = 0;
  double Asum2 = 0;
  double Bsum2 = 0;
  for(int i=0; i<steps; i++){ 
  	double theta_1 = rnd.Rndm() * 2 * ex::eth + ex::th1;
 	double theta_2 = rnd.Rndm() * 2 * ex::eth + ex::th2;
  	GetAB(ex::th0, theta_1, theta_2, A, B);
  	Asum2 += A;
  	Bsum2 += B;
  	h4.Fill(A);
  	h5.Fill(B);
  	h6.Fill(A,B);
  }  
  double Amean2 = Asum2/steps;
  double Bmean2 = Bsum2/steps;
  cout << Amean2 << "    " << Bmean2 << endl ;
  c->cd(4);
  h4.Draw();
  c->cd(5);
  h5.Draw();
  c->cd(6);
  h6.Draw("colZ");
  gApplication->Run();
  // Assumendo errore gaussiano (eth/sqrt(3)) 
  // a) calcolo dell'errore su A e su B tramite variazione delle funzione
  // b) calcolo delle distribuzioni di A e B
  //    dell'errore su A, B e della loro correlazione

  // Ripetere punto b) nel caso in cui invece si assuma distribuzione uniforme con larghezza +/-eth

  return 0;

}
