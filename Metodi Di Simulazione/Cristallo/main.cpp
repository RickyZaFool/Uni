#include "squareGrid.h"
#include "gridPainter.h"
#include <TApplication.h>

int main(int argc, char** argv) {
    // Initialize the ROOT application
    TApplication app("app", &argc, argv);

    // Create a square grid with a side length of 10 and 50% coverage
    squareGrid grid(100, 0.2);

    // Create a grid painter for the square grid
    gridPainter painter(grid);

    // Draw the grid
    painter.drawGrid();

    // Run the application
    app.Run();

    return 0;
}