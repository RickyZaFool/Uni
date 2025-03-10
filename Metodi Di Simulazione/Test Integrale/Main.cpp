#include <iostream>
#include <cmath>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TApplication.h>

using namespace std;


double funToIntegrate(double x){
	double y;
	y = 1/(2*sqrt(x));
	return y;
}

int main(){
	cout << "n of steps " ;
	int steps = 0;
	cin >> steps;
	cout << endl;
	double success = 0;
	TRandom3 rnd;
	rnd.SetSeed(time(0));
	for(int i = 0; i<steps; i++){

		double x = rnd.Rndm() + 1;
		double y = rnd.Rndm();
		if(y < funToIntegrate(x)){success++;}
		cout << i*100/steps << "%   " << endl;
	}
	cout << success/steps << endl;
	return 0;
}
