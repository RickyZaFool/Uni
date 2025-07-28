#include "squareGrid.h"
#include "gridPainter.h"
#include "crystalDeposit.h"
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
    CrystalDeposit deposit(sideLength, startingPercentageCoverage, startsOrdered);
    deposit.setFlux(0.01666666666); // Set the flux to 0.01666666666
    deposit.setTemperature(300); // Set the temperature to 300 K
    squareGrid grid = deposit.getGrid();
    // Create a grid painter for the square grid
    gridPainter painter(grid);
    
    for(int i = 0; i < 10000000; ++i) {
        deposit.step(); // Simulate a step of crystal growth
        if (i % 100000 == 0){
            std::cout << i / 10000000.0 * 100 << "% completed." << std::endl;
        }        
        if (i % 250000 == 0) { 
            std::cout << " drawing " << std::endl;
            grid = deposit.getGrid();
            painter.drawGrid();
        }
    }

    std::cout <<100 << "% completed." << std::endl;
    // Run the application
    app.Run();

    return 0;
}