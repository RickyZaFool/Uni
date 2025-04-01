#include "Grid.h"
#include <iostream>
#include <TRandom3.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>

using namespace std;

int main(){
    TApplication app("app",0,NULL);
    Grid grid(50, 1492, 0.5F, false);
    grid.PaintTheGrid();
    app.Run(true);
    return 0;
}