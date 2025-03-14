#include <TRandom3.h>
#include <iostream>
#include <cmath>

using namespace std;

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
	
	if(grid[upX][y]){
		neighbors++;
		//cout << " down neighbor " ;
	}
	if(grid[downX][y]){
		neighbors++;
		//cout << " up neighbor" ;
	}
	if(grid[x][upY]){
		neighbors++;
		//cout << " right neighbor " ;
	}
	if(grid[x][downY]){
		neighbors++;
		//cout << " left neighbor " ;
	}
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
	float elapsedTime = time(0);
	//declare a grid
	int sideLenght;
	cout << "grid size  " ;
	cin >> sideLenght;
	int steps;
	cout << endl << "steps ";
	cin >> steps;
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
	float nodesToFill = sideLenght*sideLenght/2;
	for(int i = 0; i < nodesToFill; i++){
		int x_setup = int(rnd.Rndm()*sideLenght);
		int y_setup = int(rnd.Rndm()*sideLenght);
		if(grid[x_setup][y_setup]){
			i--;
		}
		else{
			grid[x_setup][y_setup]=1;
		}
	}
	
	//SETUP GRID
	cout << "starting energy in J units " << calculateEnergy(grid, sideLenght) << endl;
	cout << "************** STARTING GRID **************" << endl;
	for(int i = 0; i < sideLenght; i++){
		for(int j = 0; j < sideLenght; j++){
			//if(i == x_debug && j == y_debug){grid[i][j] += 10; }
			if(grid[i][j]){
				cout << "[*]";
			}
			else{cout << "[ ]";}
		}cout << endl ;
	}
	
	//Setup completed
	
	//Steps:
	int x_rand, y_rand, neighs, neighs_new, x_move, y_move = 0;
	for(int s = 0; s < steps; s++){
		// select a random particle that doesn't have 0 or 4 neighbors
		int checkedParticles = 0;
		while(true){
			x_rand = int(rnd.Rndm()*sideLenght);
			y_rand = int(rnd.Rndm()*sideLenght);
			if(grid[x_rand][y_rand]){
				neighs = numberOfNeighbors(grid, x_rand, y_rand, sideLenght);
				if(neighs != 4 && neighs > 0){
					break;
				}
			}
			checkedParticles++;
		}

	//select a random direction
		x_move = x_rand;
		y_move = y_rand;
		auto [dir_x,dir_y] = getRandomDirection(rnd);
		x_move = x_rand+dir_x;
		y_move = y_rand+dir_y;
		if(x_move == sideLenght){x_move = 0;}
		if(y_move == sideLenght){y_move = 0;}
		if(x_move < 0){x_move = sideLenght-1;}
		if(y_move < 0){y_move = sideLenght-1;}
		if(grid[x_move][y_move] != 0){
			x_move = x_rand;
			y_move = y_rand;
		}
		neighs_new = numberOfNeighbors(grid, x_move, y_move, sideLenght) - 1;
		if(neighs_new < neighs || neighs_new == neighs){   //should always move.
			grid[x_rand][y_rand] = 0;
			grid[x_move][y_move] = 1;
		}
		else{
			int energyDelta = neighs_new - neighs;
			float prob = 0.002;
			float moveCheck = rnd.Rndm();
			if(moveCheck < prob){
				grid[x_rand][y_rand] = 0;
				grid[x_move][y_move] = 1;		
			}
		}
		if(roundf(20*float(s)/steps) == 20*float(s)/steps){
			cout << 100*float(s)/steps << "%   " << calculateEnergy(grid, sideLenght) << endl; //percentage buffer
		}
		if(!calculateEnergy(grid, sideLenght)){
			break;
		}
	}
	
	//DEBUG FINAL

	//int x_debug = 0;
	//int y_debug = 1;
	cout << endl << "final energy in J units " << calculateEnergy(grid, sideLenght) << endl;
	cout << "************** FINAL GRID **************" << endl;	
	for(int i = 0; i < sideLenght; i++){
		for(int j = 0; j < sideLenght; j++){
			//if(i == x_debug && j == y_debug){grid[i][j] += 10; }
			if(grid[i][j]){
				cout << "[*]";
			}
			else{cout << "[ ]";}
		}cout << endl ;
	}
	//cout << "Neighbors of debug cell " << numberOfNeighbors(grid, x_debug, y_debug, sideLenght) << endl;
	//ORDER PARAMETER P
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
	cout << cellsOnA << "  " << cellsOnB << endl;
	float p = static_cast<float>(cellsOnA - cellsOnB)/(cellsOnA + cellsOnB) ;
	cout << "Order parameter " << p << endl;
	elapsedTime = time(0) - elapsedTime;
	cout << endl <<"elapsed time:" << elapsedTime << endl; 
	return 0;
}
