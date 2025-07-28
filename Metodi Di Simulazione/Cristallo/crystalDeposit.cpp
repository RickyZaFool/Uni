#include "crystalDeposit.h"
#include <stdexcept>
#include <cmath>

double CrystalDeposit::getTemperature() const {
    return _temperature;
}
double CrystalDeposit::getFlux() const {
    return _flux;
}
void CrystalDeposit::setTemperature(double temperature) {
    if (temperature < 0) {
        throw std::invalid_argument("Temperature cannot be negative.");
    }
    _temperature = temperature;
}
void CrystalDeposit::setFlux(double flux) {
    if (flux < 0) {
        throw std::invalid_argument("Flux cannot be negative.");
    }
    _flux = flux;
}
void CrystalDeposit::setBoundEnergyOfNoNeighbor(double energy) {
    if (energy < 0) {
        throw std::invalid_argument("Bound energy of no neighbor cannot be negative.");
    }
    _boundEnergyOfNoNeighbor = energy;
}
void CrystalDeposit::setBoundEnergyOfEachNeighbor(double energy) {
    if (energy < 0) {
        throw std::invalid_argument("Bound energy of each neighbor cannot be negative.");
    }
    _boundEnergyOfEachNeighbor = energy;
}
void CrystalDeposit::setVibrationFrequency(double frequency) {
    if (frequency <= 0) {
        throw std::invalid_argument("Vibration frequency must be positive.");
    }
    _vibrationFrequency = frequency;
}

void CrystalDeposit::resetGrid() {
    // Reinitialize the grid with the original parameters
    squareGrid newGrid(getGrid().sideLenght(), getGrid().percentageCoverage(), 0); // 0 for unordered
    *this = CrystalDeposit(newGrid); // Assign the new grid to this instance
    initializeCellVectors(); // Reinitialize the cell vectors
}

void CrystalDeposit::calculateWeightOfDeposition() {
    // Calculate the weight of deposition based flux and side lenght
    _weightOfDeposition = _flux * getGrid().sideLenght() * getGrid().sideLenght();
}

void CrystalDeposit::initializeCellVectors() {
    // Clear the vectors
    _filledCells.clear();
    _cellsWithNoNeighbors.clear();
    _cellsWithOneNeighbor.clear();
    _cellsWithTwoNeighbors.clear();
    _cellsWithThreeNeighbors.clear();
    _cellsWithFourNeighbors.clear();

    // Fill the vectors based on the current state of the grid
    for (int i = 0; i < getGrid().sideLenght() * getGrid().sideLenght(); ++i) {
        if (getGrid().isCellFilled(i)) {
            _filledCells.push_back(i);
            int neighbors = getGrid().numberOfNeighbors(i);
            switch (neighbors) {
                case 0:
                    _cellsWithNoNeighbors.push_back(i);
                    break;
                case 1:
                    _cellsWithOneNeighbor.push_back(i);
                    break;
                case 2:
                    _cellsWithTwoNeighbors.push_back(i);
                    break;
                case 3:
                    _cellsWithThreeNeighbors.push_back(i);
                    break;
                case 4:
                    _cellsWithFourNeighbors.push_back(i);
                    break;
            }
        }
    }
}


void CrystalDeposit::updateCellVectorsDiffusion(int cellIndex, int hasJustMoved, int moveDirection) { 
    //This method assumes the cell at cellIndex has either just been moved to cellIndex or had a neighbor removed or added
    //This method doesn't handle the update for the old and new neighbors of the cell, it only updates the cell itself
    // If the cell is empty, remove it from all vectors
    if (!getGrid().isCellFilled(cellIndex)) {
        auto removeFromVector = [&](std::vector<int>& vec) {
            vec.erase(std::remove(vec.begin(), vec.end(), cellIndex), vec.end());
        };
        removeFromVector(_filledCells);
        removeFromVector(_cellsWithNoNeighbors);
        removeFromVector(_cellsWithOneNeighbor);
        removeFromVector(_cellsWithTwoNeighbors);
        removeFromVector(_cellsWithThreeNeighbors);
        removeFromVector(_cellsWithFourNeighbors);
        return;
    }

    // If the cell is filled and has just moved, update the vectors accordingly
    else if (hasJustMoved) {
        // Change its index in the filled cells vector
        // First, find the old index of the cell
        int oldCellIndex = -1; 
        switch (moveDirection) {
            case 0: // Moved left
                oldCellIndex = getGrid().leftNeighborIndex(cellIndex);
                break;
            case 1: // Moved right
                oldCellIndex = getGrid().rightNeighborIndex(cellIndex);
                break;
            case 2: // Moved up
                oldCellIndex = getGrid().topNeighborIndex(cellIndex);
                break;
            case 3: // Moved down
                oldCellIndex = getGrid().bottomNeighborIndex(cellIndex);
                break;
            default:
                throw std::invalid_argument("Invalid move direction for updating cell vectors.");
        }
        // Now change old cell index to the new from the filled cells vector
        auto it = std::find(_filledCells.begin(), _filledCells.end(), oldCellIndex);
        if (it != _filledCells.end()) {
            *it = cellIndex; // Update the index in the filled cells vector
        }

        int oldNeighbors = -1; // Initialize with an invalid value

        // Calculate the number of neighbors the cell had before moving to find in which vector to remove it from
        switch (moveDirection) {
            case 0: // Moved left
                oldNeighbors = getGrid().numberOfNeighbors(oldCellIndex); // Decrease to avoid counting the moved cell
                break;
            case 1: // Moved right
                oldNeighbors = getGrid().numberOfNeighbors(oldCellIndex); // Decrease to avoid counting the moved cell
                break;
            case 2: // Moved up
                oldNeighbors = getGrid().numberOfNeighbors(oldCellIndex); // Decrease to avoid counting the moved cell
                break;
            case 3: // Moved down
                oldNeighbors = getGrid().numberOfNeighbors(oldCellIndex); // Decrease to avoid counting the moved cell
                break;
            default:
                throw std::invalid_argument("Invalid move direction for updating cell vectors.");
        }

        // Remove the cell from the old neighbors vector, because it has just moved and does not belong there anymore
        // The oldNeighbors variable is used to determine which vector to remove the cell from
        switch (oldNeighbors) {
            case 0:
                _cellsWithNoNeighbors.erase(std::remove(_cellsWithNoNeighbors.begin(), _cellsWithNoNeighbors.end(), oldCellIndex), _cellsWithNoNeighbors.end());
                break;
            case 1:
                _cellsWithOneNeighbor.erase(std::remove(_cellsWithOneNeighbor.begin(), _cellsWithOneNeighbor.end(), oldCellIndex), _cellsWithOneNeighbor.end());
                break;
            case 2:
                _cellsWithTwoNeighbors.erase(std::remove(_cellsWithTwoNeighbors.begin(), _cellsWithTwoNeighbors.end(), oldCellIndex), _cellsWithTwoNeighbors.end());
                break;
            case 3:
                _cellsWithThreeNeighbors.erase(std::remove(_cellsWithThreeNeighbors.begin(), _cellsWithThreeNeighbors.end(), oldCellIndex), _cellsWithThreeNeighbors.end());
                break;
        } //A cell with 4 neighbors cannot have just moved, so we do not handle that case here

        // Add the cell to the new neighbors vector
        int newNeighbors = getGrid().numberOfNeighbors(cellIndex);
        switch (newNeighbors) {
            case 0:
                _cellsWithNoNeighbors.push_back(cellIndex);
                break;
            case 1:
                _cellsWithOneNeighbor.push_back(cellIndex);
                break;
            case 2:
                _cellsWithTwoNeighbors.push_back(cellIndex);
                break;
            case 3:
                _cellsWithThreeNeighbors.push_back(cellIndex);
                break;
        } // The cell cannot have 4 neighbors after moving, so we do not handle that case here
    }
    
    else { // The cell has witnessed a neighbor being removed or added
        int neighbors = getGrid().numberOfNeighbors(cellIndex);
        switch (neighbors) {
            case 0:
                // Cell had one neighbor, now it has none
                _cellsWithOneNeighbor.erase(std::remove(_cellsWithOneNeighbor.begin(), _cellsWithOneNeighbor.end(), cellIndex), _cellsWithOneNeighbor.end());
                _cellsWithNoNeighbors.push_back(cellIndex);
                break;
            case 1:
                // Cell had two neighbors or none, now it has one
                _cellsWithNoNeighbors.erase(std::remove(_cellsWithNoNeighbors.begin(), _cellsWithNoNeighbors.end(), cellIndex), _cellsWithNoNeighbors.end());
                _cellsWithTwoNeighbors.erase(std::remove(_cellsWithTwoNeighbors.begin(), _cellsWithTwoNeighbors.end(), cellIndex), _cellsWithTwoNeighbors.end());
                _cellsWithOneNeighbor.push_back(cellIndex);
                break;
            case 2:
                // Cell had three neighbors or one, now it has two
                _cellsWithOneNeighbor.erase(std::remove(_cellsWithOneNeighbor.begin(), _cellsWithOneNeighbor.end(), cellIndex), _cellsWithOneNeighbor.end());
                _cellsWithThreeNeighbors.erase(std::remove(_cellsWithThreeNeighbors.begin(), _cellsWithThreeNeighbors.end(), cellIndex), _cellsWithThreeNeighbors.end());
                _cellsWithTwoNeighbors.push_back(cellIndex);
                break;
            case 3:
                // Cell had four or two neighbors, now it has three
                _cellsWithTwoNeighbors.erase(std::remove(_cellsWithTwoNeighbors.begin(), _cellsWithTwoNeighbors.end(), cellIndex), _cellsWithTwoNeighbors.end());
                _cellsWithFourNeighbors.erase(std::remove(_cellsWithFourNeighbors.begin(), _cellsWithFourNeighbors.end(), cellIndex), _cellsWithFourNeighbors.end());
                _cellsWithThreeNeighbors.push_back(cellIndex);
                break;
            case 4:
                // Cell had three neighbors, now it has four
                _cellsWithThreeNeighbors.erase(std::remove(_cellsWithThreeNeighbors.begin(), _cellsWithThreeNeighbors.end(), cellIndex), _cellsWithThreeNeighbors.end());
                _cellsWithFourNeighbors.push_back(cellIndex);
            default:
                throw std::invalid_argument("Invalid number of neighbors for updating cell vectors.");
        }
    }
}

void CrystalDeposit::diffuse(int numberOfNeighbors) {
    // Move one random cell with the given number of neighbors
    std::vector<int>* targetVector = nullptr;
    switch (numberOfNeighbors) {
        case 0:
            // Must find a cell with no neighbors
            targetVector = &_cellsWithNoNeighbors;
            break;
        case 1:
            targetVector = &_cellsWithOneNeighbor;
            break;
        case 2:
            targetVector = &_cellsWithTwoNeighbors;
            break;
        case 3:
            targetVector = &_cellsWithThreeNeighbors;
            break;
        default:
            throw std::invalid_argument("Invalid number of neighbors for diffusion.");
    }
    if (targetVector->empty()) {
        throw std::runtime_error("No cells available for diffusion with the specified number of neighbors.");
    }

    
    
    int randomIndex = rand() % targetVector->size();
    int cellIndex = (*targetVector)[randomIndex];

    int randomDirection = -1; // Initialize with an invalid direction
    int neighborIndex = -1; 
    // Randomly select a neighbor to move to
    while(true){
        randomDirection = rand() % 4; // 0: left, 1: right, 2: up, 3: down
        neighborIndex;
        switch (randomDirection) {
            case 0:
                neighborIndex = getGrid().leftNeighborIndex(cellIndex);
                break;
            case 1:
                neighborIndex = getGrid().rightNeighborIndex(cellIndex);
                break;
            case 2:
                neighborIndex = getGrid().topNeighborIndex(cellIndex);
                break;
            case 3:
                neighborIndex = getGrid().bottomNeighborIndex(cellIndex);
                break;
            default:
                throw std::runtime_error("Invalid random direction for diffusion.");
        }
        if (!getGrid().isCellFilled(neighborIndex)) {
            // Move the occupant to the neighbor
            getGrid().moveOccupant(cellIndex, neighborIndex);
            // Update the vectors
            // One of the four neighbors of the old position is now filled and has just moved: the cell at neighborIndex, that is being handled by one of the four following calls
            // Example: if the cell at cellIndex moved left, then the cell at getGrid().leftNeighborIndex(cellIndex) has just moved there, and should be flagged as having just moved
            updateCellVectorsDiffusion(getGrid().leftNeighborIndex(cellIndex), static_cast<int>(randomDirection == 0), randomDirection);
            updateCellVectorsDiffusion(getGrid().rightNeighborIndex(cellIndex), static_cast<int>(randomDirection == 1), randomDirection);
            updateCellVectorsDiffusion(getGrid().topNeighborIndex(cellIndex), static_cast<int>(randomDirection == 2), randomDirection);
            updateCellVectorsDiffusion(getGrid().bottomNeighborIndex(cellIndex), static_cast<int>(randomDirection == 3), randomDirection);
            // One of the four neighbors of the new position is now empty and will be handled by one of the four following calls
            // Example: if the cell at cellIndex moved left, then the cell at getGrid().rightNeighborIndex(neighborIndex) is empty. This will be detected in the updateCellVectorsDiffusion method
            updateCellVectorsDiffusion(getGrid().leftNeighborIndex(neighborIndex), 0, randomDirection);
            updateCellVectorsDiffusion(getGrid().rightNeighborIndex(neighborIndex), 0, randomDirection);
            updateCellVectorsDiffusion(getGrid().topNeighborIndex(neighborIndex), 0, randomDirection);
            updateCellVectorsDiffusion(getGrid().bottomNeighborIndex(neighborIndex), 0, randomDirection);
            return; // Exit after successful diffusion
        }
    }
}

void CrystalDeposit::updateCellVectorsDeposit(int cellIndex) {
    // This method assumes the cell at cellIndex has just been filled

    // Add it to the filled cells vector
    _filledCells.push_back(cellIndex);

    int neighbors = getGrid().numberOfNeighbors(cellIndex);
    switch (neighbors) {
        case 0:
            _cellsWithNoNeighbors.push_back(cellIndex);
            break;
        case 1:
            _cellsWithOneNeighbor.push_back(cellIndex);
            break;
        case 2:
            _cellsWithTwoNeighbors.push_back(cellIndex);
            break;
        case 3:
            _cellsWithThreeNeighbors.push_back(cellIndex);
            break;
        case 4:
            _cellsWithFourNeighbors.push_back(cellIndex);
            break;
        default:
            throw std::invalid_argument("Invalid number of neighbors for updating cell vectors.");
    }

    // Update the vectors of the neighbors
    for (int i = 0; i < 4; ++i) { // Check all four neighbors
        int neighborIndex = -1;
        switch (i) {
            case 0: // Left
                neighborIndex = getGrid().leftNeighborIndex(cellIndex);
                break;
            case 1: // Right
                neighborIndex = getGrid().rightNeighborIndex(cellIndex);
                break;
            case 2: // Up
                neighborIndex = getGrid().topNeighborIndex(cellIndex);
                break;
            case 3: // Down
                neighborIndex = getGrid().bottomNeighborIndex(cellIndex);
                break;
            default:
                throw std::invalid_argument("Invalid direction for updating cell vectors.");
        }
        if (getGrid().isCellFilled(neighborIndex)) {
            int neighborCount = getGrid().numberOfNeighbors(neighborIndex);
            switch (neighborCount) {
                case 0: // If the neighbor has no neighbors after the deposition there has been a mistake
                    throw std::runtime_error("Neighbor cannot have zero neighbors after deposition.");
                case 1:
                    _cellsWithNoNeighbors.erase(std::remove(_cellsWithNoNeighbors.begin(), _cellsWithNoNeighbors.end(), neighborIndex), _cellsWithNoNeighbors.end());
                    _cellsWithOneNeighbor.push_back(neighborIndex);
                    break;
                case 2:
                    _cellsWithOneNeighbor.erase(std::remove(_cellsWithOneNeighbor.begin(), _cellsWithOneNeighbor.end(), neighborIndex), _cellsWithOneNeighbor.end());
                    _cellsWithTwoNeighbors.push_back(neighborIndex);
                    break;
                case 3:
                    _cellsWithTwoNeighbors.erase(std::remove(_cellsWithTwoNeighbors.begin(), _cellsWithTwoNeighbors.end(), neighborIndex), _cellsWithTwoNeighbors.end());
                    _cellsWithThreeNeighbors.push_back(neighborIndex);
                    break;
                case 4:
                    _cellsWithThreeNeighbors.erase(std::remove(_cellsWithThreeNeighbors.begin(), _cellsWithThreeNeighbors.end(), neighborIndex), _cellsWithThreeNeighbors.end());
                    _cellsWithFourNeighbors.push_back(neighborIndex);
                    break;
                default:
                    throw std::invalid_argument("Invalid number of neighbors for updating cell vectors.");
            }
        }
    }
}

void CrystalDeposit::deposit(){
    int randomIndex = -1; // Initialize with an invalid index
    while(true){
        randomIndex = rand() % (getGrid().sideLenght() * getGrid().sideLenght());
        if (!getGrid().isCellFilled(randomIndex)) {
            // If the cell is empty, fill it
            getGrid().fillCell(randomIndex);
            // Update the vectors
            updateCellVectorsDeposit(randomIndex);
            return; // Exit after successful deposition
        }
    }
}

