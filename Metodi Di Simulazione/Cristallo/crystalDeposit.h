#include "squareGrid.h"
#include <stdexcept>
#include <cmath>
#include <array>
#include <vector>

#ifndef CRYSTALDEPOSIT_H
#define CRYSTALDEPOSIT_H

class CrystalDeposit : public squareGrid {

public:
    CrystalDeposit(int sideLength, double startingPercentageCoverage = 0, int startsOrdered = 0, double temperature = 300.0, double flux = 0.01666666666) 
        : squareGrid(sideLength, startingPercentageCoverage, startsOrdered), _temperature(temperature), _flux(flux) {
            initializeCellVectors(); // Initialize the cell vectors based on the grid state
            calculateWeightOfDeposition(); // Calculate the weight of deposition based on the initial parameters
        }
    CrystalDeposit(const squareGrid& grid, double temperature = 300.0, double flux = 0.01666666666) 
        : squareGrid(grid), _temperature(temperature), _flux(flux) {
            initializeCellVectors(); // Initialize the cell vectors based on the grid state
            calculateWeightOfDeposition(); // Calculate the weight of deposition based on the initial parameters
        }

    // Getters for the grid
    squareGrid& getGrid() {
        return *this; // Return the grid itself
    }

    // Getters for temperature and flux
    double getTemperature() const;
    double getFlux() const;

    // Setters for internal parameters
    void setTemperature(double temperature);
    void setFlux(double flux);
    void setBoundEnergyOfNoNeighbor(double energy);
    void setBoundEnergyOfEachNeighbor(double energy);
    void setVibrationFrequency(double frequency); 

    // Methods to simulate crystal growth based on temperature and flux
    void step();
    void simulateGrowth(int numberOfSteps);

    // Reset the grid to its initial state
    void resetGrid();

private:
    double _temperature; // Temperature of the crystal deposit
    double _flux;        // Flux of the crystal deposit
    double _boundEnergyOfNoNeighbor = 0.4 * 1.602176634e-19; // In J
    double _boundEnergyOfEachNeighbor = 0.2 * 1.602176634e-19; // In J

    double _vibrationFrequency = 10e12; // Vibration frequency of the crystal deposit
    double _boltzmannConstant = 1.380649e-23; // Boltzmann constant in J/K
    int _numberOfSteps = 1000; // Number of steps for the simulation

    std::vector<int> _filledCells; // Vector to store filled cells
    std::vector<int> _cellsWithNoNeighbors; // Vector to store cells with no neighbors
    std::vector<int> _cellsWithOneNeighbor; // Vector to store cells with one neighbor
    std::vector<int> _cellsWithTwoNeighbors; // Vector to store cells with two neighbors
    std::vector<int> _cellsWithThreeNeighbors; // Vector to store cells with three neighbors
    std::vector<int> _cellsWithFourNeighbors; // Vector to store cells with four neighbors

    double _weightOfDeposition; // Weight of deposition based on side length and flux
    void calculateWeightOfDeposition();

    void initializeCellVectors(); // initialize vectors based on current state of the grid
    void updateCellVectorsDiffusion(int cellIndex, int hasJustMoved, int moveDirection); // Update the vectors after a diffusion step
    

    // Tresholds for the various moves
    double _tresholdForNoNeighbors = 0; // Treshold for moving from a cell with no neighbors
    double _tresholdForOneNeighbor = 0; // Treshold for moving from a cell with one neighbor
    double _tresholdForTwoNeighbors = 0; // Treshold for moving from a cell with two neighbors
    double _tresholdForThreeNeighbors = 0; // Treshold for moving from a cell with three neighbors
    double _tresholdForDeposit = 0; // Treshold for depositing a new cell
    double calculateTotalWeight();

    void diffuse(int numberOfNeighbors); // Move one random cell with the given number of neighbors
    void deposit(); // Deposit a new cell in the grid
    void updateCellVectorsDeposit(int cellIndex); // Update the vectors after a deposition step

};

#endif