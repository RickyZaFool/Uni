#include "squareGrid.h"
#include "gridPainter.h"
#include <TApplication.h>
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    // Initialize the ROOT application
    TApplication app("app", &argc, argv);

    // Open a configuration file that contains the grid parameters
    std::ifstream configFile("config.txt");
    if (!configFile.is_open()) {
        std::cerr << "Error opening configuration file." << std::endl;
        return 404;
    }
    // The file is expected to contain a header of one line explaining the file format, the side length, the starting percentage coverage, and whether the grid starts ordered (0 or 1). 
    // Last two parameters are optional.
    int sideLength = -1;
    double startingPercentageCoverage = 0.0;
    bool startsOrdered = false;

    while (configFile.peek() == '#') { // Skip comments
        std::string line;
        std::getline(configFile, line);
    }
    configFile >> sideLength;
    if (configFile.peek() != '\n') {
        configFile >> startingPercentageCoverage;
        if (configFile.peek() != '\n') {
            configFile >> startsOrdered;
        }
    }
    
    if(sideLength <= 0) {
        std::cerr << "Invalid side length: " << sideLength << ". It must be a positive integer." << std::endl;
        return 1;
    }

    // Create a square grid
    squareGrid grid(sideLength, startingPercentageCoverage, startsOrdered);

    // Create a grid painter for the square grid
    gridPainter painter(grid);

    // Draw the grid
    painter.drawGrid();

    // Run the application
    app.Run();

    return 0;
}