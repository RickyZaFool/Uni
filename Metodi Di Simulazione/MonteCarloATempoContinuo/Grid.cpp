#include <iostream>
#include "Grid.h"
#include <TRandom3.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>


void Grid::Grid(int sideLength, GridStatus status){
    SideLength = sideLength;
    NumberOfParticles = 0;
    grid = std::vector<int>(SideLength*SideLength, 0);
}

void Grid::Grid(int sideLength, int seed = -1, float theta = 0.5, bool ordered = false){
    
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
            for (int particle = 0; particle < numberOfParticles; particle++) {
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
