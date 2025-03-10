#include <TRandom3.h>
#include <iostream>
#include <cmath>

using namespace std;

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


int main(){
	//declare a grid
	int sideLenght;
	cout << "grid size  " ;
	cin >> sideLenght;
	vector<vector<int>> grid(sideLenght,vector<int>(sideLenght));
	//set each node to 0
	for(int i = 0; i < sideLenght; i++){
		for(int j = 0; j < sideLenght; j++){
			grid[i][j] = 0;
		}
	}
	//fill with a random configuration, half of the nodes filled with particles
	TRandom3 rnd;
	rnd.SetSeed(1492);
	int nodesToFill = sideLenght*sideLenght/2;
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
	
	//DEBUG SETUP
	cout << "REMEMBER TO COMMENT DEBUG SECTION" << endl;
	cout << "starting energy in J units " << calculateEnergy(grid, sideLenght) << endl;
	cout << "************** STARTING GRID **************" << endl;
	for(int i = 0; i < sideLenght; i++){
		for(int j = 0; j < sideLenght; j++){
			//if(i == x_debug && j == y_debug){grid[i][j] += 10; }
			cout << "[" << grid[i][j] << "]";
		}cout << endl ;
	}	
	
	//Setup completed
	
	//Steps:
	//TODO: select a random particle, check if it can move, check against probability, if so move it, then check energy
	
	
	//DEBUG FINAL

	//int x_debug = int(rnd.Rndm()*sideLenght);
	//int y_debug = int(rnd.Rndm()*sideLenght);
	cout << "final energy in J units " << calculateEnergy(grid, sideLenght) << endl;
	cout << "************** FINAL GRID **************" << endl;	
	for(int i = 0; i < sideLenght; i++){
		for(int j = 0; j < sideLenght; j++){
			//if(i == x_debug && j == y_debug){grid[i][j] += 10; }
			cout << "[" << grid[i][j] << "]";
		}cout << endl ;
	}
	return 0;
}
