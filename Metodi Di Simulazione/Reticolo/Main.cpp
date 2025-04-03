#include "Grid.h"
#include <TApplication.h>
#include <fstream>
#include <TRandom3.h>
using namespace std;



void classifyAtoms(vector<int>& q0, vector<int>& q1, vector<int>& q2, vector<int>& q3, Grid grid){
	int nOfParticles = grid.GetNumberOfParticles();
	for(int i = 0; i<nOfParticles; i++){
		int neighs = grid.NumberOfNeighbors(grid.PosOfParticle(i));
		switch (neighs)
		{
		case 0:
			q0.push_back(i);
			break;
		case 1:
			q1.push_back(i);
			break;
		case 2:
			q2.push_back(i);
			break;
		case 3:
			q3.push_back(i);
			break;
		default:
			break;
		}
	}
}


int main(){
	TRandom3 rand;
	TApplication app("app",0,NULL);
	ifstream file("gridInput.txt");
	vector<int> q0, q1, q2, q3;

	//Input Read
	int sl;
	file >> sl ;
	int seed;
	file >> seed;
	if(seed == -1){
        rand.SetSeed(time(0));
    }else{rand.SetSeed(seed);}
	float theta;
	file >> theta;
	bool ordered;
	file >> ordered;
	int particlesToPlace;
	file >> particlesToPlace;
	float f;
	file >> f;
	int nu;
	file >> nu;
	float E0, Eb;
	file >> E0 >> Eb;
	E0 = E0 *11604;				//Kb = 1
	Eb = Eb *11604;
	int Tmin, Tmax;
	file >> Tmin >> Tmax;
	//Input read end

	
	int X, Y;
	Grid grid(sl, seed, theta, ordered);
	cout << particlesToPlace << endl;
	for(int i=0; i<particlesToPlace; i++){
		X = rand.Rndm()*grid.GetSideLength();
		Y = rand.Rndm()*grid.GetSideLength();
		while(grid.IsOccupied(X,Y)){
			X = rand.Rndm()*grid.GetSideLength();
			Y = rand.Rndm()*grid.GetSideLength();		
		}
		grid.PlaceParticle(X,Y);
	}

	float DepositionWeight = f*grid.GetSideLength()*grid.GetSideLength();
	float qWeight = 

	classifyAtoms(q0, q1, q2, q3, grid);
	cout << q0.size() << " " << q1.size() << " " << q2.size() << " " << q3.size() << endl;






	grid.PaintTheGrid();
	app.Run();
	return 0;
}
