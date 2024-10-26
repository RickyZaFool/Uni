
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TLegend.h>
#include "OdeSolver.h"
#include "Vector3.h"
#include "MatPoint.h"

using namespace std;

Vector3 fInternal(unsigned int i,unsigned int j, double t, vector<MatPoint> p){
  Vector3 ipos = p[i].R();
  Vector3 force = p[i].Mass()*p[j].GravField(ipos);
  return force;
}

Vector3 fExternal(unsigned int i, double t, vector<MatPoint> p){
  return Vector3();
}

int main(){
  string method;
  double giorno = 86400; // giorno in secondi
  double simLenght = 365; double simDelta = 1;
  cout << "Please input the simulation lenght in days " << endl; 
  cin >> simLenght;
  simLenght *= giorno;
  cout << "Please input the simulation step in tenth of a day " << endl; 
  cin >> simDelta;
  cout << "Please input solve method (Eulero, Rk2, VelVel)" << endl;
  cin >> method;

  while(true){
    if(method == "Rk2" || method == "Eulero" || method == "VelVel"){
      break;
    }
    else{
      cout << "Only valid method are Eulero, Rk2, VelVel" << endl;
      cin >> method;
    }
  }
  simDelta *= (0.1*giorno);
  //Lettura dei dati dal file
  double mass;
  double x,y,z,vx,vy,vz;
  string name = "";
  ifstream f("fileInput.dat");
  vector<MatPoint> bodies;
  while(f >> name >> mass >> x >> y >> z >> vx >> vy >> vz){
    bodies.push_back(MatPoint(mass, 0.0, name, Vector3(x,y,z) ,Vector3(vx,vy,vz)));
  }
  OdeSolver ode(method, bodies);

  
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  ode.fInternal = fInternal;
  ode.fExternal = fExternal;
  ode.DeltaT(simDelta);
  
//Creazione dei grafici (uno per pianeta)
  vector<TGraph> gr(ode.N());
  TCanvas c("c","",10,10,1200,1200);



  //Preparazione grafico delle coordinate dei pianeti
  double au = 1.5e8;   // unita' astronimica in km
  double size = 5*au;  // 5 unita' astronimiche
  gPad->DrawFrame(-size,-size,size,size);
  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed-7,kRed+2,kCyan-8,kBlue-7,kBlue+1,kBlue+2};
  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(0,ode.GetMatPoint(i).R().X(),ode.GetMatPoint(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerStyle(20); gr[i].SetMarkerSize(0.05);
    if (i==0) gr[i].SetMarkerSize(1);
    gr[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();

  Vector3 initMomentum;
  Vector3 endMomentum;
  for(unsigned int i=0;i<ode.N();i++){
    initMomentum = initMomentum + (ode.GetMatPoints()[i].R().Cross(ode.GetMatPoints()[i].V()*ode.GetMatPoints()[i].Mass())) * (pow(10,-16));
  }
  cout << "initial momentum " << initMomentum << "*10^16" <<endl;
  

  //Run del metodo numerico + grafico in tempo reale delle coordinate e del mom. angolare totale
  string percent = "";
  while (ode.T()<simLenght){
    ode.Step();
    for (unsigned int i=0;i<ode.N();i++){
      int j = gr[i].GetN();
      gr[i].SetPoint(j,ode.GetMatPoint(i).R().X(),ode.GetMatPoint(i).R().Y());
    }
    gPad->Modified(); gPad->Update();
    gSystem->ProcessEvents();
    percent = to_string(ode.T()*100/(simLenght)) + "%";
    c.SetTitle(percent.c_str());
  }
  c.SetTitle("done");
  for(unsigned int i=0;i<ode.N();i++){
    endMomentum = endMomentum + (ode.GetMatPoints()[i].R().Cross(ode.GetMatPoints()[i].V()*ode.GetMatPoints()[i].Mass())) * (pow(10,-16));
  }
  cout << "end momentum " << endMomentum << "*10^16" <<endl;
  cout << "momentum difference " << endMomentum - initMomentum << endl;
  app.Run(true);


  
  return 0;
}
