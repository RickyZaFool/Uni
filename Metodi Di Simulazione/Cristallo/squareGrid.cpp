#include "squareGrid.h"
#include <stdexcept>
#include <cmath>
#include <array>

squareGrid::squareGrid(int sideLenght, double startingPercentageCoverage, bool startsOrdered) {
    if (sideLenght <= 0) {
        throw std::invalid_argument("Side length must be a positive integer.");
    }
    if (startingPercentageCoverage < 0 || startingPercentageCoverage > 1) {
        throw std::invalid_argument("Starting percentage coverage must be between 0 and 1.");
    }
    
    _sideLenght = sideLenght;
    _absoluteCoverage = static_cast<int>(sideLenght * sideLenght * startingPercentageCoverage); // Calculate absolute coverage based on the side length and starting percentage
    _percentageCoverage = startingPercentageCoverage;

    grid = new int[sideLenght * sideLenght]; // Initialize the grid with zeros
    if (startsOrdered) {
        // Fill the grid in a checkerboard pattern
        for (int i = 0; i < sideLenght; ++i) {
            for (int j = 0; j < sideLenght; ++j) {
                if ((i + j) % 2 == 0 && _absoluteCoverage > 0) {
                    grid[i * sideLenght + j] = 1; // Fill the cell
                    --_absoluteCoverage;
                } else {
                    grid[i * sideLenght + j] = 0; // Leave the cell empty
                }
            }
        } // Then if the absolute coverage is not met, fill the remaining cells randomly
        if(_absoluteCoverage > 0) {
            int filledCells = 0;
            while (filledCells < _absoluteCoverage) {
                int x = rand() % sideLenght;
                int y = rand() % sideLenght;
                int index = coordinatesToIndex(x, y);
                if (grid[index] == 0) { // If the cell is empty
                    grid[index] = 1; // Fill the cell
                    ++filledCells;
                }
            }
        }
    } else {
        // Randomly fill cells based on the starting percentage coverage
        int filledCells = 0;
        while (filledCells < _absoluteCoverage) {
            int x = rand() % sideLenght;
            int y = rand() % sideLenght;
            int index = coordinatesToIndex(x, y);
            if (grid[index] == 0) { // If the cell is empty
                grid[index] = 1; // Fill the cell
                ++filledCells;
            }
        }
    }

    // Reset absolute coverage after initialization
    _absoluteCoverage = 0; 
    for (int i = 0; i < sideLenght * sideLenght; ++i) {
        if (grid[i] != 0) {
            _absoluteCoverage++;
        }
    }

    // Calculate the percentage coverage
    _percentageCoverage = static_cast<double>(_absoluteCoverage) / (sideLenght * sideLenght);
    

}

squareGrid::~squareGrid() {
    delete[] grid; // Free the allocated memory for the grid
}

std::array<int, 2> squareGrid::indexToCoordinates(int index) const {
    if (index < 0 || index >= _sideLenght * _sideLenght) {
        throw std::out_of_range("Index out of range.");
    }
    std::array <int, 2> coordinates;
    coordinates[0] = index / _sideLenght; // Row
    coordinates[1] = index % _sideLenght; // Column 
    return coordinates;
}

int squareGrid::coordinatesToIndex(int x, int y) const {
    if (x < 0 || x >= _sideLenght || y < 0 || y >= _sideLenght) {
        throw std::out_of_range("Coordinates out of range.");
    }
    return x * _sideLenght + y; // Convert coordinates to index
}

int squareGrid::coordinatesToIndex(std::array<int, 2> coordinates) const {
    return coordinatesToIndex(coordinates[0], coordinates[1]);
}

int squareGrid::leftNeighborIndex(std::array<int, 2> coordinates) const {
    if (coordinates[1] == 0) {
        return coordinatesToIndex(coordinates[0], _sideLenght - 1); // Wrap around to the last column
    }
    return coordinatesToIndex(coordinates[0], coordinates[1] - 1);
}

int squareGrid::leftNeighborIndex(int index) const {
    std::array<int, 2> coordinates = indexToCoordinates(index);
    return leftNeighborIndex(coordinates);
}

int squareGrid::leftNeighborIndex(int x, int y) const {
    return leftNeighborIndex(coordinatesToIndex(x, y));
}

int squareGrid::rightNeighborIndex(std::array<int, 2> coordinates) const {
    if (coordinates[1] == _sideLenght - 1) {
        return coordinatesToIndex(coordinates[0], 0); // Wrap around to the first column
    }
    return coordinatesToIndex(coordinates[0], coordinates[1] + 1);
}

int squareGrid::rightNeighborIndex(int index) const {
    std::array<int, 2> coordinates = indexToCoordinates(index);
    return rightNeighborIndex(coordinates);
}

int squareGrid::rightNeighborIndex(int x, int y) const {
    return rightNeighborIndex(coordinatesToIndex(x, y));
}

int squareGrid::topNeighborIndex(std::array<int, 2> coordinates) const {
    if (coordinates[0] == 0) {
        return coordinatesToIndex(_sideLenght - 1, coordinates[1]); // Wrap around to the last row
    }
    return coordinatesToIndex(coordinates[0] - 1, coordinates[1]);
}

int squareGrid::topNeighborIndex(int index) const {
    std::array<int, 2> coordinates = indexToCoordinates(index);
    return topNeighborIndex(coordinates);
}

int squareGrid::topNeighborIndex(int x, int y) const {
    return topNeighborIndex(coordinatesToIndex(x, y));
}

int squareGrid::bottomNeighborIndex(std::array<int, 2> coordinates) const {
    if (coordinates[0] == _sideLenght - 1) {
        return coordinatesToIndex(0, coordinates[1]); // Wrap around to the first row
    }
    return coordinatesToIndex(coordinates[0] + 1, coordinates[1]);
}

int squareGrid::bottomNeighborIndex(int index) const {
    std::array<int, 2> coordinates = indexToCoordinates(index);
    return bottomNeighborIndex(coordinates);
}

int squareGrid::bottomNeighborIndex(int x, int y) const {
    return bottomNeighborIndex(coordinatesToIndex(x, y));
}

int squareGrid::sideLenght() const {
    return _sideLenght;
}

int squareGrid::filledCells() const {
    return _absoluteCoverage; // Return the number of filled cells
}

double squareGrid::percentageCoverage() const {
    return _percentageCoverage; // Return the percentage coverage
}

bool squareGrid::isCellFilled(int x, int y) const {
    if (x < 0 || x >= _sideLenght || y < 0 || y >= _sideLenght) {
        throw std::out_of_range("Coordinates out of range.");
    }
    return grid[coordinatesToIndex(x, y)] != 0; // Check if the cell is filled
}

bool squareGrid::isCellFilled(int index) const {
    if (index < 0 || index >= _sideLenght * _sideLenght) {
        throw std::out_of_range("Index out of range.");
    }
    return grid[index] != 0; // Check if the cell is filled
}

bool squareGrid::isCellFilled(std::array<int, 2> coordinates) const {
    return isCellFilled(coordinates[0], coordinates[1]); // Check if the cell is filled using coordinates
}

void squareGrid::fillCell(int x, int y) {
    if (x < 0 || x >= _sideLenght || y < 0 || y >= _sideLenght) {
        throw std::out_of_range("Coordinates out of range.");
    }
    int index = coordinatesToIndex(x, y);
    if (grid[index] == 0) { // If the cell is empty
        grid[index] = 1; // Fill the cell
        _absoluteCoverage++;
        _percentageCoverage = static_cast<double>(_absoluteCoverage) / (_sideLenght * _sideLenght);
    }
}

void squareGrid::fillCell(int index) {
    if (index < 0 || index >= _sideLenght * _sideLenght) {
        throw std::out_of_range("Index out of range.");
    }
    if (grid[index] == 0) { // If the cell is empty
        grid[index] = 1; // Fill the cell
        _absoluteCoverage++;
        _percentageCoverage = static_cast<double>(_absoluteCoverage) / (_sideLenght * _sideLenght);
    }
}

void squareGrid::fillCell(std::array<int, 2> coordinates) {
    fillCell(coordinates[0], coordinates[1]); // Fill the cell using coordinates
}

void squareGrid::emptyCell(int x, int y) {
    if (x < 0 || x >= _sideLenght || y < 0 || y >= _sideLenght) {
        throw std::out_of_range("Coordinates out of range.");
    }
    int index = coordinatesToIndex(x, y);
    if (grid[index] != 0) { // If the cell is filled
        grid[index] = 0; // Empty the cell
        _absoluteCoverage--;
        _percentageCoverage = static_cast<double>(_absoluteCoverage) / (_sideLenght * _sideLenght);
    }
}

void squareGrid::emptyCell(int index) {
    if (index < 0 || index >= _sideLenght * _sideLenght) {
        throw std::out_of_range("Index out of range.");
    }
    if (grid[index] != 0) { // If the cell is filled
        grid[index] = 0; // Empty the cell
        _absoluteCoverage--;
        _percentageCoverage = static_cast<double>(_absoluteCoverage) / (_sideLenght * _sideLenght);
    }
}

void squareGrid::emptyCell(std::array<int, 2> coordinates) {
    emptyCell(coordinates[0], coordinates[1]); // Empty the cell using coordinates
}

void squareGrid::moveOccupant(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= _sideLenght * _sideLenght || toIndex < 0 || toIndex >= _sideLenght * _sideLenght) {
        throw std::out_of_range("Index out of range.");
    }
    if (grid[fromIndex] != 0 && grid[toIndex] == 0) { // If the from cell is filled and the to cell is empty
        grid[toIndex] = grid[fromIndex]; // Move occupant
        grid[fromIndex] = 0; // Empty the from cell
    }
}

void squareGrid::moveOccupant(int fromX, int fromY, int toX, int toY) {
    if (fromX < 0 || fromX >= _sideLenght || fromY < 0 || fromY >= _sideLenght || toX < 0 || toX >= _sideLenght || toY < 0 || toY >= _sideLenght) {
        throw std::out_of_range("Coordinates out of range.");
    }
    int fromIndex = coordinatesToIndex(fromX, fromY);
    int toIndex = coordinatesToIndex(toX, toY);
    moveOccupant(fromIndex, toIndex); // Move occupant using indices
}

void squareGrid::moveOccupant(std::array<int, 2> fromCoordinates, std::array<int, 2> toCoordinates) {
    moveOccupant(fromCoordinates[0], fromCoordinates[1], toCoordinates[0], toCoordinates[1]); // Move occupant using coordinates
}
