#include "GridInputManager.h"
#include <fstream>
#include "Grid.h"

GridInputManager(string filename){
    int toCall = 0;
    ifstream file(filename);
    file >> sideLenght >> seed >> theta >> ordered;
    if(theta == 0){
        status = GridStatus::Empty;
    }
}
	
bool GridInputManager::HasErrors(){

}
	
Grid GridInputManager::CreateGrid(){

}
	
int GridInputManager::ReadSideLenght(){

}
	
int GridInputManager::ReadSeed(){

}
	
float GridInputManager::ReadTheta(){

}
	
bool GridInputManager::IsOrdered(){

}
	
	
