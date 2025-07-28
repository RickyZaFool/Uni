#include <array>

/*
    The grid is a square grid of cells, each cell can be either occupied or not. Occupied cells are represented by a value of 1, while unoccupied cells are represented by a value of 0.
    The grid is represented as a 1D array for simplicity.
    The grid can be initialized with a specific side length and an optional starting percentage of coverage.
    The grid can also be initialized in an ordered state, where cells are filled in a checkerboard pattern.
    Once initialized, the grid allows to retrieve information about its size, coverage, and the state of individual cells and their adjacent cells.
    There are also methods to modify the grid, such as filling a cell, emptying a cell, and move the occupant of a cell to an adjacent cell. 
*/

#ifndef SQUAREGRID_H
#define SQUAREGRID_H

class squareGrid{
    public:
        
        // Constructor
        squareGrid(int sideLenght, double startingPercentageCoverage = 0, bool startsOrdered = false); // Starting percentage coverage should be between 0 and 1. If not ordered, the grid will be filled randomly.

        // Coordinates and index conversion
        std::array<int, 2> indexToCoordinates(int index) const;
        int coordinatesToIndex(int x, int y) const;
        int coordinatesToIndex(std::array<int, 2> coordinates) const;

        // Neighbor indices
        int leftNeighborIndex(int index) const;
        int leftNeighborIndex(int x, int y) const;
        int leftNeighborIndex(std::array<int, 2> coordinates) const;
        
        int rightNeighborIndex(int index) const;
        int rightNeighborIndex(int x, int y) const;
        int rightNeighborIndex(std::array<int, 2> coordinates) const;
        
        int topNeighborIndex(int index) const;
        int topNeighborIndex(int x, int y) const;
        int topNeighborIndex(std::array<int, 2> coordinates) const;
        
        int bottomNeighborIndex(int index) const;
        int bottomNeighborIndex(int x, int y) const;
        int bottomNeighborIndex(std::array<int, 2> coordinates) const;

        // Getters
        int sideLenght() const;
        int filledCells() const;
        double percentageCoverage() const;
        bool isCellFilled(int x, int y) const;
        bool isCellFilled(int index) const;
        bool isCellFilled(std::array<int, 2> coordinates) const;

        // Cell modification
        void fillCell(int x, int y);
        void fillCell(int index);
        void fillCell(std::array<int, 2> coordinates);

        void emptyCell(int x, int y);
        void emptyCell(int index);
        void emptyCell(std::array<int, 2> coordinates);
        
        void moveOccupant(int fromX, int fromY, int toX, int toY);
        void moveOccupant(int fromIndex, int toIndex);
        void moveOccupant(std::array<int, 2> fromCoordinates, std::array<int, 2> toCoordinates);

        // Delete grid
        ~squareGrid();

    private:

        int _sideLenght;
        int _absoluteCoverage;
        double _percentageCoverage;
        int* grid; // Placeholder for grid, actual size will be set in constructor

};

#endif