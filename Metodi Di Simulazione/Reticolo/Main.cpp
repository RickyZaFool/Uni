#include <TRandom3.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
//FILE
ofstream ofile("data.dat");
//DIRECTIONS TO KEEP IT CLEAN
const vector<pair<int, int>> directions = {
    {0, -1},  // Up
    {0, 1},   // Down
    {-1, 0},  // Left
    {1, 0}    // Right
};
//DIRECTION PICKER AT RANDOM
pair<int, int> getRandomDirection(TRandom3& rnd) {
    int randomIndex = int(rnd.Rndm()*3); // Generates a random number from 0 to 3
    return directions[randomIndex]; // Return the corresponding direction
}
//NUMBER OF NEIGHBORS START
int numberOfNeighbors(vector<vector<int>> grid, int x, int y, int sideLenght){
	int neighbors = 0;
	int upX = x+1;
	int downX = x-1;
	int upY = y+1;
	int downY = y-1;
	if(upX == sideLenght){upX = 0;}
	if(upY == sideLenght){upY = 0;}
	if(downX < 0){downX = sideLenght-1;}
	if(downY < 0){downY = sideLenght-1;}
	if(grid[upX][y]){neighbors++;}
	if(grid[downX][y]){neighbors++;}
	if(grid[x][upY]){neighbors++;}
	if(grid[x][downY]){neighbors++;}
	return neighbors;
}
//NUMBER OF NEIGHBORS END
//CALCULATE ENERGY START
double calculateEnergy(vector<vector<int>> grid, int sideLenght){
	int interactions = 0;
	for(int i = 0; i < sideLenght; i++){
		for(int j = 0; j < sideLenght; j++){
			if(grid[i][j]){
				interactions+= numberOfNeighbors(grid, i, j, sideLenght);
			}
		}
	}
	double energy = interactions/2.0;
	return energy;
}
//CALCULATE ENERGY END
//MAIN START
int main(){
	//declare a grid
	int sideLenght;
	cout << "grid size  " ;
	cin >> sideLenght;
	int MCS;
	cout << endl << "MCS ";
	cin >> MCS;
	cout << endl;
	vector<vector<int>> grid(sideLenght,vector<int>(sideLenght));
	//set each node to 0
	for(int i = 0; i < sideLenght; i++){
		for(int j = 0; j < sideLenght; j++){
			grid[i][j] = 0;
		}
	}
	//fill with a random configuration, a fraction of the nodes filled with particles
	TRandom3 rnd;
	rnd.SetSeed(time(0));
	float theta = 0.5;
	float nOfParticles = sideLenght*sideLenght*theta;
	//Particles position arrays
	int X[int(nOfParticles)] = {0};
	int Y[int(nOfParticles)] = {0};
	for(int i = 0; i < nOfParticles; i++){
		int x_setup = int(rnd.Rndm()*sideLenght);
		int y_setup = int(rnd.Rndm()*sideLenght);
		if(grid[x_setup][y_setup]){
			i--;
		}
		else{
			grid[x_setup][y_setup]=1;
			X[i] = x_setup;
			Y[i] = y_setup;
		}
	}	
	//START GRID DEBUG
	cout << "************** STARTING GRID **************" << endl;
	for(int i = 0; i < sideLenght; i++){
		for(int j = 0; j < sideLenght; j++){
			if(grid[i][j]){
				cout << "[*]";
			}
			else{cout << "[ ]";}
		}cout << endl ;
	}
	//Setup completed
	int x_rand = 0, y_rand = 0, neighs = 0, neighs_new = 0, x_move = 0, y_move = 0;
	float p = 0;
	float psum = 0;
	float pmean = 0;
	//NEWSTEPS with 2 loops
	for(int m = 0; m < MCS; m++){ //Start mcs
		for(int step = 0; step < nOfParticles; step++){ //Start internal loop
			//select random particle
			int random_particle = int(rnd.Rndm()*nOfParticles);
			x_rand = X[random_particle];
			y_rand = Y[random_particle];
			if(!grid[x_rand][y_rand]){ //DEBUG >
				cout << "Error 404 particle not found" << endl;
			} // < DEBUG
			//select random direction
			x_move = x_rand;
			y_move = y_rand;
			auto [dir_x,dir_y] = getRandomDirection(rnd);
			x_move = x_rand+dir_x;
			y_move = y_rand+dir_y;
			//PACMAN YEAHHHHH
			if(x_move == sideLenght){x_move = 0;}
			if(y_move == sideLenght){y_move = 0;}
			if(x_move < 0){x_move = sideLenght-1;}
			if(y_move < 0){y_move = sideLenght-1;}
			if(!grid[x_move][y_move]){ //Start destination check
				neighs = numberOfNeighbors(grid, x_rand, y_rand, sideLenght);
				neighs_new = numberOfNeighbors(grid, x_move, y_move, sideLenght) - 1;
				int energyDelta = neighs_new - neighs;
				float betaj = 4;
				float prob = exp(-betaj*(energyDelta));
				float moveCheck = rnd.Rndm();
				if(moveCheck < prob){//Start prob move check
					grid[x_rand][y_rand] = 0;
					grid[x_move][y_move] = 1;
					X[random_particle] = x_move;
					Y[random_particle] = y_move;
				}//End prob move check
			} //End destination check
		} //End internal loop
		if(m % 20 == 0){
			int cellsOnA = 0, cellsOnB = 0;
			for(int i = 0; i < sideLenght; i++){
				for(int j = 0; j < sideLenght; j++){
					if(grid[i][j]){
						if((i+j) % 2 != 0){
							cellsOnA++;
						}
						else{
							cellsOnB++;
						}
					}
				}
			}
			p = static_cast<float>(cellsOnA - cellsOnB)/(cellsOnA + cellsOnB);
			ofile << p << endl;
			psum += p;
		}
		if(int(float(m)*100/MCS) == float(m)*100/MCS){
			cout << float(m)*100/MCS << "%  " << p << endl;
		}
	} //End mcs
	pmean = 20 * psum / MCS;
	cout << "order parameter mean " << pmean << endl;
	cout << "************** FINAL GRID **************" << endl;
	for(int i = 0; i < sideLenght; i++){
		for(int j = 0; j < sideLenght; j++){
			if(grid[i][j]){
				cout << "[*]";
			}
			else{cout << "[ ]";}
		}cout << endl ;
	}
	return 0;
} //End main
