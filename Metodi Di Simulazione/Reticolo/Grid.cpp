#include <iostream>
#include "Grid.h"
#include <TRandom3.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TStyle.h>


Grid::Grid(int sideLength, GridStatus status){
    SideLength = sideLength;
    NumberOfParticles = 0;
    grid = std::vector<int>(SideLength*SideLength, 0);
}

Grid::Grid(int sideLength, int seed, float theta, bool ordered){
    
    //Set the seed, if void, set time(0) as seed
    Seed = seed;
    if(Seed == -1){
        Rnd.SetSeed(time(0));
    }else{Rnd.SetSeed(Seed);}

    //Setup the grid
    SideLength = sideLength;
    grid = std::vector<int>(SideLength*SideLength);
    NumberOfParticles = int(SideLength*SideLength*theta);
    positions = std::vector<int>(NumberOfParticles);
    
    if(ordered){
        if(theta > 0.5){
            std::cout << "**********************************************************************************************" << std::endl;     // maybe do this in the future?
            std::cout << "WARNING: Ordered grid for theta greater than half is not yet supported, switching to unordered" << std::endl;     // maybe do this in the future?
            std::cout << "**********************************************************************************************" << std::endl;     // maybe do this in the future?
            for(int particle = 0; particle < NumberOfParticles; particle++){    
                int setupPosition = Rnd.Rndm()*(SideLength*SideLength); 
                if(!grid[setupPosition]){   
                    grid[setupPosition] = 1;    
                    positions[particle] = setupPosition;    
                }else{particle--;}
            }
        }
        else{
            int setupPosition = 0;
            for (int particle = 0; particle < NumberOfParticles; particle++) {
                int row = setupPosition / sideLength;
                int col = setupPosition % sideLength;
                if ((row + col) % 2 == 0) {
                    grid[setupPosition] = 1;
                    positions[particle] = setupPosition;
                }
                else{
                    particle--;
                }
            }
        }
    }
    else{
        for(int particle = 0; particle < NumberOfParticles; particle++){
            int setupPosition = Rnd.Rndm()*(SideLength*SideLength);
            if(!grid[setupPosition]){
                grid[setupPosition] = 1;
                positions[particle] = setupPosition;
            }else{particle--;}
        }
    }

}

int Grid::PosInGrid(int X, int Y){
    int pos = X + Y*SideLength;
    return pos;
}

int Grid::XOfPosition(int position){
    return position % SideLength;
}

int Grid::YOfPosition(int position){
    return position / SideLength;
}

int Grid::UpNeighbor(int position){
    int currentX = XOfPosition(position);
    int currentY = YOfPosition(position);
    int newY = (currentY - 1 + SideLength)%SideLength;
    return PosInGrid(currentX, newY);
}

int Grid::DownNeighbor(int position){
    int currentX = XOfPosition(position);
    int currentY = YOfPosition(position);
    int newY = (currentY + 1 + SideLength)%SideLength;
    return PosInGrid(currentX, newY);
}

int Grid::LeftNeighbor(int position){
    int currentX = XOfPosition(position);
    int currentY = YOfPosition(position);
    int newX = (currentX - 1 + SideLength)%SideLength;
    return PosInGrid(newX, currentY);
}

int Grid::RightNeighbor(int position){
    int currentX = XOfPosition(position);
    int currentY = YOfPosition(position);
    int newX = (currentX + 1 + SideLength)%SideLength;
    return PosInGrid(newX, currentY);
}

void Grid::PlaceParticle(int position){
    positions.push_back(position);
    grid[position] = 1;
    NumberOfParticles++;
}

void Grid::PlaceParticle(int X, int Y){
    int pos = PosInGrid(X, Y);
    PlaceParticle(pos);
}

void Grid::RemoveParticleInSpot(int position){
    for (auto it = positions.begin(); it != positions.end(); ++it) {
        if(*it == position){
            positions.erase(it);
            break;
        }
    }
    grid[position] = 0;
    NumberOfParticles--;
}

void Grid::RemoveParticleInSpot(int X, int Y){
    int pos = PosInGrid(X, Y);
    RemoveParticleInSpot(pos);
}

void Grid::RemoveParticleOfIndex(int particle){
    int pos = positions[particle];
    positions.erase(positions.begin()+ particle);
    grid[pos] = 0;
    NumberOfParticles--;
}

int Grid::PosOfParticle(int particle){
    return positions[particle];
}

int Grid::XOfParticle(int particle){
    int X = XOfPosition(positions[particle]);
    return X;
}

int Grid::YOfParticle(int particle){
    int Y = YOfPosition(positions[particle]);
    return Y;
}

bool Grid::IsOccupied(int position){
    if(grid[position]){
        return true;
    }else{return false;}
}

bool Grid::IsOccupied(int X, int Y){
    int pos = PosInGrid(X, Y);
    bool isOcc = IsOccupied(pos);
    return isOcc;
}

void Grid::PaintTheGrid(){
    TH2D histo("histo", "Sim", SideLength, 0.0, SideLength, SideLength, 0.0, SideLength);
    for(int spot = 0; spot < SideLength*SideLength; spot++){
        histo.SetBinContent(XOfPosition(spot)+1,YOfPosition(spot)+1,grid[spot]);
    }
    gStyle->SetOptStat(0);
    gStyle->SetPalette(kInvertedDarkBodyRadiator);
    histo.Draw("Colz");
    gPad->Update();
    gSystem->ProcessEvents();
}

int Grid::GetNumberOfParticles(){
    NumberOfParticles = positions.size();
    return NumberOfParticles;
}

int Grid::GetSideLength(){
    return SideLength;
}

int Grid::GetSeed(){
    return Seed;
}

void Grid::Move(int particle, int direction){
    int pos = PosOfParticle(particle);
    int newPos = pos;
    switch (direction)
    {
    case 0:
        newPos = UpNeighbor(pos);
        if(!grid[newPos]){
            grid[newPos] = 1;
            grid[pos] = 0;
            positions[particle] = newPos;
        }
        break;
    case 1:
        newPos = LeftNeighbor(pos);
        if(!grid[newPos]){
            grid[newPos] = 1;
            grid[pos] = 0;
            positions[particle] = newPos;
        }
        break;
    case 2:
        newPos = DownNeighbor(pos);
        if(!grid[newPos]){
            grid[newPos] = 1;
            grid[pos] = 0;
            positions[particle] = newPos;
        }
        break;
    case 3:
        newPos = RightNeighbor(pos);
        if(!grid[newPos]){
            grid[newPos] = 1;
            grid[pos] = 0;
            positions[particle] = newPos;
        }
        break;
    
    
    default:
        break;
    }
}

void Grid::Move(int particle){
    int  dir = Rnd.Rndm()*3;
    Move(particle, dir);
}

int Grid::NumberOfNeighbors(int position){
    int neighs = 0;
    if(grid[UpNeighbor(position)]){neighs++;}
    if(grid[DownNeighbor(position)]){neighs++;}
    if(grid[LeftNeighbor(position)]){neighs++;}
    if(grid[RightNeighbor(position)]){neighs++;}
    return neighs;
}