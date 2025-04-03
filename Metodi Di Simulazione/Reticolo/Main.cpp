#include "Grid.h"
#include <TApplication.h>

int main(){
	TApplication app("app",0,NULL);
	Grid grid1(8, GridStatus::Empty);
	grid1.PlaceParticle(4,4);
	grid1.Move(0, 0);
	grid1.PlaceParticle(4,4);
	grid1.PaintTheGrid();
	app.Run();
	return 0;
}
