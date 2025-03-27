/*

CONVENTIONS USED
all internal variables start with capital letters and have capitals to separate words
all functions start with capital letters
all temporary variables and function parameters start with low letters and have capitals to separate words

*/
#ifndef GRIDCLASS
#define GRIDCLASS
#include <iostream>
#include <TRandom3.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

class GridMSAF
{
public:

    void SetGridSeed(int seed);
    void Setup(int sideLenght, float theta, bool ordered);
    void Move(int particle, int direction);
    void PaintTheGrid();
    int FindPosIndex(int x, int y);
    int FindXFromPos(int position);
    int FindYFromPos(int position);
    int ParticlePos(int particle);
    int ParticleX(int particle);
    int ParticleY(int particle);
    bool IsOccupied(int position);
    bool IsOccupied(int x, int y);
    int CheckNeighbors(int position);
    int GetNumberOfParticles();
    
private:
    int SideLenght;
    int Seed = -1;
    int NumberOfParticles;
    TRandom3 Rnd;
    std::vector<int> Grid;
    std::vector<int> ParticlesPositions;
};

#endif