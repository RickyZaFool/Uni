#include <iostream>
#include <fstream>
#include <TMath.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TApplication.h>
using namespace std;

const vector<string> filenames {
	"GIOIE.dat" ,
	"8V D60 T240 .5S.dat",
	"10V D60 T240 .5S.dat",
	"12V D60 T240 .5S.dat",
	"12V D60 T240 .5S pt2.dat",
	"9V D60 T240 1S.dat",
	"12V D60 T240 1S.dat",
	"9V D60 T240 2S.dat"
};

int main(){
	TApplication app("app",0,NULL);
	TCanvas c1;
	c1.Divide(4 , 2);
	vector<TGraph> gr(filenames.size());
	for(unsigned long int file=0; file < filenames.size(); file++ ){
		c1.cd(file+1);
		float time=0, V=0, uselessV=0;
		int i = 0;
		ifstream ifile(filenames[file]);
		gr[file].SetTitle(filenames[file].c_str());
		while(ifile >> time >> V >> uselessV){
			
			gr[file].SetPoint(i,time,V);
			i++;	
			gr[file].Draw();
		}
		c1.Update();
	}
	/*
	TGraphErrors g1;
	while(ifile >> time >> V >> uselessV){
		g1.SetPoint(i,time,V);
		i++;
	}
	*/
	cout << "gets here" << endl;
	app.Run(true);
	return 0;
}