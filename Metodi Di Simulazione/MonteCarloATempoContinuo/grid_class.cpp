#include <iostream>
#include "grid_class.h"
#include <TRandom3.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>


void GridMSAF::SetGridSeed(int seed){
    Rnd.SetSeed(seed);
}

void GridMSAF::Setup(int sideLenght, float theta, bool ordered){
    TCanvas c("c", "Simulation", 800, 600);
    SideLenght = sideLenght;
    if(Seed == -1){
        Rnd.SetSeed(time(0));
    }else{Rnd.SetSeed(Seed);}
    NumberOfParticles = int(SideLenght*SideLenght*theta);
    Grid = std::vector<int>(SideLenght*SideLenght);
    ParticlesPositions = std::vector<int>(NumberOfParticles);
    if(ordered){
        if(theta <= 0.5){
            for(int i=0; i<NumberOfParticles; i++){
                if(SideLenght % 2 != 0){
                    Grid[2*i] = 1;
                    ParticlesPositions[i] = 2 * i;
                }
                else{
                    int tempIndex = 2 * i + 1 * ((i % (SideLenght/2)) ^ 1);
                    Grid[tempIndex] = 1;
                    ParticlesPositions[i] = tempIndex;
                }
            }
        }
        else{
            std::cout << "**********************************************************************************************" << std::endl;
            std::cout << "WARNING: Ordered grid for theta greater than half is not yet supported, switching to unordered" << std::endl;
            std::cout << "**********************************************************************************************" << std::endl;
            for(int i=0; i<NumberOfParticles; i++){
                int setupPos = int(Rnd.Rndm()*SideLenght*SideLenght);
                if(!Grid[setupPos]){
                    Grid[setupPos] = 1;
                    ParticlesPositions[i] = setupPos;
                }else{i--;}
            }
        }
    }
    else{
        for(int i=0; i<NumberOfParticles; i++){
            int setupPos = int(Rnd.Rndm()*SideLenght*SideLenght);
            if(!Grid[setupPos]){
                Grid[setupPos] = 1;
                ParticlesPositions[i] = setupPos;
            }else{i--;}
        }
    }
}

void GridMSAF::Move(int particle, int direction){
    int originPos = ParticlesPositions[particle];
    int originX = FindXFromPos(originPos);
    int originY = FindYFromPos(originPos);
    int newX, newY;
    switch (direction)
    {
    case 0:                   //UP
        newX = originX;
        newY = (originY - 1 + SideLenght)%SideLenght;
        break;
    case 1:                   //RIGHT
        newX = (originX + 1 + SideLenght)%SideLenght;
        newY = originY;
        break;
    case 2:                   //DOWN
        newX = originX;
        newY = (originY + 1 + SideLenght)%SideLenght;
        break;
    case 3:                   //LEFT
        newX = (originX - 1 + SideLenght)%SideLenght;
        newY = originY;
        break;
    }
    int newPos = FindPosIndex(newX, newY);
    if(!Grid[newPos]){
        Grid[originPos] = 0;
        Grid[newPos] = 1;
        ParticlesPositions[particle] = newPos;
    }
}

int GridMSAF::GetNumberOfParticles(){
    return NumberOfParticles;
}

int GridMSAF::FindPosIndex(int x, int y){
    return x + SideLenght * y;
}

int GridMSAF::FindXFromPos(int position){
    return position % SideLenght;
}

int GridMSAF::FindYFromPos(int position){
    return position / SideLenght;
}

bool GridMSAF::IsOccupied(int position){
    return bool(Grid[position]);
}

bool GridMSAF::IsOccupied(int x, int y){
    return bool(Grid[FindPosIndex(x,y)]);
}

int GridMSAF::ParticlePos(int particle){
    return ParticlesPositions[particle];
}

int GridMSAF::ParticleX(int particle){
    return FindXFromPos(ParticlesPositions[particle]);
}

int GridMSAF::ParticleY(int particle){
    return FindYFromPos(ParticlesPositions[particle]);
}

void GridMSAF::PaintTheGrid(){
    TH2D histo("histo", "Sim", SideLenght, 0.0, SideLenght, SideLenght, 0.0, SideLenght);
    for(int location = 0; location < SideLenght*SideLenght; location++){
        histo.SetBinContent(FindXFromPos(location)+1,FindYFromPos(location)+1,Grid[location]);
    }
    histo.Draw("COLZ");
    gPad->Update();
    gSystem->ProcessEvents();
}

int GridMSAF::CheckNeighbors(int position){
    int originX = FindXFromPos(position);
    int originY = FindYFromPos(position);
    int newX, newY;
    int neighbors = 0;
    for(int direction = 0; direction < 4; direction++){
        switch (direction)
        {
        case 0:                   //UP
            newX = originX;
            newY = (originY - 1 + SideLenght)%SideLenght;
            if(IsOccupied(newX,newY)){
                neighbors++;
            }
            break;
        case 1:                   //RIGHT
            newX = (originX + 1 + SideLenght)%SideLenght;
            newY = originY;
            if(IsOccupied(newX,newY)){
                neighbors++;
            }
            break;
        case 2:                   //DOWN
            newX = originX;
            newY = (originY + 1 + SideLenght)%SideLenght;
            if(IsOccupied(newX,newY)){
                neighbors++;
            }
            break;
        case 3:                   //LEFT
            newX = (originX - 1 + SideLenght)%SideLenght;
            newY = originY;
            if(IsOccupied(newX,newY)){
                neighbors++;
            }
            break;
        }
    }
    return neighbors;
}