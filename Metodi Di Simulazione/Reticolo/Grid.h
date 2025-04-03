#ifndef GRID
#define GRID
#include <iostream>
#include <TRandom3.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

enum class GridStatus { Empty };

class Grid
{
public:

    //constructors
    Grid(int sideLength, GridStatus status);                                              //This constructors creates a completely empty or full grid.
    Grid(int sideLength, int seed = -1, float theta = 0.5, bool ordered = false);
    
    //functions that handle the coordinates
    int PosInGrid(int X, int Y);
    int XOfPosition(int position);
    int YOfPosition(int position);
    int UpNeighbor(int position);
    int DownNeighbor(int position);
    int LeftNeighbor(int position);
    int RightNeighbor(int position);

    //functions that place particles on the grid
    void PlaceParticle(int position);
    void PlaceParticle(int X, int Y);

    //functions that remove particles from the grid
    void RemoveParticleInSpot(int position);
    void RemoveParticleInSpot(int X, int Y);
    void RemoveParticleOfIndex(int particle);

    //functions that find a particle's position
    int PosOfParticle(int particle);
    int XOfParticle(int particle);
    int YOfParticle(int particle);
    
    //functions that check if a position is occupied
    bool IsOccupied(int position);
    bool IsOccupied(int X, int Y);    
    
    //functions that show informations about the grid
    void PaintTheGrid();
    int GetNumberOfParticles();
    int GetSideLength();
    int GetSeed();

    //function that moves a particle
    void Move(int particle, int direction);

    
private:


    std::vector<int> grid;
    std::vector<int> positions;
    TRandom3 Rnd;
    int SideLength;
    int Seed;
    int NumberOfParticles;
    
};

#endif