#include "grid_class.h"
#include <TApplication.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <fstream>
using namespace std;

GridMSAF Grid;

float calculateP(GridMSAF grid){
    int particlesOnA = 0;
    int particlesOnB = 0;
    int N = grid.GetNumberOfParticles();
    for(int i = 0; i < N; i++){
        int X = grid.ParticleX(i);
        int Y = grid.ParticleY(i);
        if((X+Y)%2 == 0){
            particlesOnA++;
        }else{particlesOnB++;}
    }
    float p = float(particlesOnA - particlesOnB)/N;
    return p;
}

int main(){
    ofstream ofile("data.dat");
    int Seed = -1;
	cout << "Seed (-1 to have random seed)";
	cin >> Seed;
    TRandom3 rand;
    int MCS = 100000;
	cout << "MCS ";
	cin >> MCS;
    int sideLenght = 20;
	cout << "side lenght ";
	cin >> sideLenght;
    float betaj = 0;
	cout << "beta*j ";
	cin >> betaj;
    bool isOrdered = false;
    string order = "n";
	cout << "ordered? (y or n) ";
	cin >> order;
    if(order == "y"){
        isOrdered = true;
        cout << "ordered " << endl;
    }
    if(Seed != -1){
        rand.SetSeed(Seed);
        Grid.SetGridSeed(Seed);
    }else{rand.SetSeed(time(0));}

    TApplication app("app",0,NULL);
    Grid.Setup(sideLenght, 0.5 , isOrdered);
    Grid.PaintTheGrid();
    for (int mcs = 0; mcs < MCS; mcs++)
    {
        for(int step = 0; step < Grid.GetNumberOfParticles(); step++){
            int RandomParticle = rand.Rndm()*Grid.GetNumberOfParticles();
            int RandomDirection = rand.Rndm()*3;

            int selectedX = Grid.FindXFromPos(Grid.ParticlePos(RandomParticle));
            int selectedY = Grid.FindYFromPos(Grid.ParticlePos(RandomParticle));
            int newX, newY;
            switch (RandomDirection)
            {
            case 0:                   //UP
                newX = selectedX;
                newY = (selectedY - 1 + sideLenght)%sideLenght;
                break;
            case 1:                   //RIGHT
                newX = (selectedX + 1 + sideLenght)%sideLenght;
                newY = selectedY;
                break;
            case 2:                   //DOWN
                newX = selectedX;
                newY = (selectedY + 1 + sideLenght)%sideLenght;
                break;
            case 3:                   //LEFT
                newX = (selectedX - 1 + sideLenght)%sideLenght;
                newY = selectedY;
                break;
            }
            int RandomDestination = Grid.FindPosIndex(newX,newY);
            float DeltaEnergy =  Grid.CheckNeighbors(RandomDestination) - Grid.CheckNeighbors(Grid.ParticlePos(RandomParticle)) - 1;
            float prob = exp(-betaj * DeltaEnergy);
            float check = rand.Rndm();
            if(check < prob){
                Grid.Move(RandomParticle, RandomDirection);
            }
        }
        if(!(mcs%20)){
            //Grid.PaintTheGrid();
            ofile << calculateP(Grid) << endl; 
        }
    }
    cout << "end" << endl;
    Grid.PaintTheGrid();
    app.Run();
    return 0;
}