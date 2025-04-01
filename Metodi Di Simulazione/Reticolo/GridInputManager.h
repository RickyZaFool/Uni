#ifndef GRIDINMNG
#define GRIDINMNG
#include <fstream>
#include "Grid.h"

class GridInputManager
{
public:

	GridInputManager(string filename);
	bool HasErrors();
	Grid CreateGrid();
	int ReadSideLenght();
	int ReadSeed();
	float ReadTheta();
	bool IsOrdered();

private:

	bool hasErrors;
	int sideLenght;
	int seed;
	GridStatus status;
	float theta;
	bool ordered;
	
}

#endif
