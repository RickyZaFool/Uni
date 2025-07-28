#include "squareGrid.h"
#include <TH2D.h>
#include <TCanvas.h>

class gridPainter {

public:
    // Constructor
    gridPainter(const squareGrid& grid);

    // Method to draw the grid
    void drawGrid();

private:
    const squareGrid& _grid; // Reference to the squareGrid object
    TH2D* _histogram; // Histogram to represent the grid
    TCanvas* _canvas; // Canvas to draw the histogram

};