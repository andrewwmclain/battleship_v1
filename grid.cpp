// Title: Lab 4 - grid.cpp
//
// Purpose: Implement the ship placement portion of the Battleship "grid" ADT.
//          This Lab 4 version uses a C++ struct to represent a grid
//
// Class: CSC 2430 Winter 2020
// Author: Andrew McLain
//
#include <iostream>
#include <assert.h>
#include "grid.h"
#include <fstream>
#include <sstream>

// Initialize the grid struct
//      Set counts of deployed and sunk ships to zero
//      Set the SquareStatus of all grid squares equal to Water
// Parameters:
//      grid - a grid struct
// Returns:
//      nothing
// Possible Errors:
//      none

void Init(Grid& grid){
    //set everything to 0
    grid.shipsDeployed = 0;
    grid.shipsSunk = 0;
    grid.shipsSunk = 0;
    //set each square to water
    for(size_t i = 0; i < COUNT_ROWS; i++){
        for(size_t j = 0; j < COUNT_COLUMNS; j++){
            grid.squareStatus[i][j] = WATER;
        }
    }
}

// Read the ship configuration for a grid from a text file stream.  Here's an example of
//      how the file is structured:
//          5
//          Submarine
//          3 1 0 0
//          Battleship
//          4 0 9 0
//          Destroyer
//          3 0 3 3
//          PatrolBoat
//          2 1 4 4
//          Carrier
//          5 1 4 5
//      where the first line is the count of ships.  Two lines are used to specify the
//      configuration of a ship.  The first line gives the ship's name.  The second line
//      contains four numbers specifying size, isVertical, startRow, and startColumn
// Parameters:
//      grid - a grid struct
//      file - an open file stream
// Returns:
//      succcess/failure
// Possible Errors:
//     File read error
//     # of ships out of range
//     Value of isVertical, startRow or startColumn out of range
//     Ship placement would extend beyong grid
//     Ship placement would overlap ship that has already been placed

bool LoadShips(Grid& grid, ifstream& file){
    string name;
    int size;
    bool isVertical;
    int row;
    int column;
    int shipsDeployed;
    //if the file cannot be read properly, return false to LoadShipsOnGrid
    if(!file.good()){
        return false;
    }
    //get # of ships deployed, if there are too many return false to LoadShipsOnGrid
    file >> shipsDeployed;
    if(shipsDeployed > 5){
        cerr << "too many ships specified\n";
        return false;
    }
    //for the number of ships deployed, try adding each one to the grid. If unable to
    //do so return false to LoadShipsOnGrid
    for(size_t i = 0; i < shipsDeployed; i++){
        file >> name;
        file >> size;
        file >> isVertical;
        file >> row;
        file >> column;
        if(!AddShip(grid, name, size, isVertical, row, column)){
            return false;
        }
    }
    return true;
}
// Save the ship configuration for a grid to a text file stream.  For the file format
//      Refer to the header comment for Load.
// Parameters:
//      grid - a grid struct
//      file - an open file stream
// Returns:
//      succcess/failure
// Possible Errors:
//     File write error

bool SaveShips(const Grid& grid, ofstream& file){
    //if the file cannot be copied to, return false to SaveShipsOnGrid
    if(!file.good()){
        return false;
    }
    //copy # of ships deployed on first line
    file << grid.shipsDeployed << "\n";
    //for each ship, input the properly formatted info to the file
    for(size_t i = 0; i < grid.shipsDeployed; i++){
        file << grid.ships[i].name << "\n";
        file << grid.ships[i].size << " ";
        file << grid.ships[i].isVertical << " ";
        file << grid.ships[i].startRow << " ";
        file << grid.ships[i].startColumn << "\n";
    }
    return true;
}
// Randomly place the indicated ships on an empty grid.
//      The grid is initialized and then random values of isVertical, startRow, and startColumn
//      are generated to place the ships.  If the random values would result in a placement that
//      does not fit within the grid or which overlaps an existing ship placement, new random
//      values will generated.  Multiple of attempts for each ship will be made until each of the
//      ships can be placed on the grid without extending beyond the grid boundaries or overlapping.
// Parameters:
//      grid - a grid struct
//      ship - an array of ship structs with their name and size fields filled in -- other
//             fields of the ship structs are ignored
//      countShips - the number of ships in the array -- must not exceed SHIPS_MAX
// Returns:
//      nothing
// Possible Errors:
//      none

void RandomlyPlaceShips(Grid& grid, const Ship ships[], int countShips){
    //Initialize the grid
    Init(grid);
    bool isVertical;
    int startRow;
    int startColumn;
    //for each ship, try adding it to the grid with the random configuration.
    //if it doesn't fit, generate a new random configuration and try again
    for(size_t i = 0; i < countShips; i++){
        do{
            isVertical = rand() % 2;
            startRow = rand() % COUNT_ROWS;
            startColumn = rand() % COUNT_COLUMNS;
        }while(!AddShip(grid, ships[i].name, ships[i].size, isVertical, startRow, startColumn));
    }
}
// Attempt to place a ship on the grid.  Checks that the placement would not cause
//      the ship to extend outside the grid or overlap another ship that has already
//      been placed on the grid.
// Parameters:
//      grid - a grid struct
//      name - name of ship to be placed
//      size - number of squares the ship covers
//      isVertical - whether the ship should be placed vertically or horizontally
//      startRow - row of uppermost square (if isVertical) or leftmost square (if !isVertical)
//      startColumn - column of uppermost square (if isVertical) or leftmost square (if !isVertical)
// Returns:
//      true if the ship can be placed, false if it would extend outside grid or overlap another ship
// Possible Errors:
//      Too many ships deployed
//      Size or position of ship is not reasonable
//      Ship placement would extend outside gird
//      Ship placement would overlap another ship


bool AddShip(Grid& grid, const string& name, int size, bool isVertical, int startRow, int startColumn){
    //if no more ships can be added, return false to calling function
    if(grid.shipsDeployed > 5){
        return false;
    }
    //if ship is being placed off the grid, return false to calling function
    if(startRow >= 10 || startRow < 0 ||
       startColumn >= 10 || startColumn < 0){
        return false;
    }
    //make sure the ship will not go off the grid before designating squares
    //and placing it
    if(isVertical){
        if(startRow + size >= 10){
            return false;
        }
        for(size_t j = 0; j < size; j++){
            if(grid.squareStatus[startRow + j][startColumn] != WATER) {
                return false;
            }
        }
        for(size_t j = 0; j < size; j++){
            grid.squareStatus[startRow + j][startColumn] = SHIP;
        }
    }
    else {
        if (startColumn + size >= 10) {
            return false;
        }
        for(size_t j = 0; j < size; j++){
            if(grid.squareStatus[startRow][startColumn + j] != WATER){
                return false;
            }
        }
        for(size_t j = 0; j < size; j++){
            grid.squareStatus[startRow][startColumn + j] = SHIP;
        }
    }

    //update the ships array in the grid
    grid.shipsDeployed++;
    grid.ships[grid.shipsDeployed - 1].hits = 0;
    grid.ships[grid.shipsDeployed - 1].name = name;
    grid.ships[grid.shipsDeployed - 1].size = size;
    grid.ships[grid.shipsDeployed - 1].isVertical = isVertical;
    grid.ships[grid.shipsDeployed - 1].startRow = startRow;
    grid.ships[grid.shipsDeployed - 1].startColumn = startColumn;

    return true;
}

// Returns the number of ships that have been sunk
// Parameters:
//      grid - a grid struct
// Returns:
//      number of ships
// Possible Errors:
//      none

int GetShipsSunk(const Grid& grid){
    return grid.shipsSunk;
}
// Returns the number of ships placed on the grid
// Parameters:
//      grid - a grid struct
// Returns:
//      number of ships
// Possible Errors:
//      none

int GetShipsDeployed(const Grid& grid){
    return grid.shipsDeployed;
}

// Retrieves information about the i-th ship.  Meant to used
// in a loop to fetch information about each the ships
// Parameters:
//      grid - a grid struct
//      i - index of ship that ranges between 0 to number of ships deployed -1
//      ship - struct to be filled with information about ship
// Returns:
//      nothing
// Possible Errors:
//      asserts that index is within range

void GetShip(const Grid& grid, int i, Ship& ship){
    assert(i >= 0 && i < grid.shipsDeployed);
    ship = grid.ships[i];
}

// Determines if there is a ship covering the specified square.  If found, returns
// the configuration index of the ship
// Parameters:
//      grid - a grid struct
//      row - row of the square
//      column - column of the square
// Returns:
//      < 0 if not found, otherwise returns the index of the ship
// Possible Errors:
//      none

int FindShip(const Grid& grid, int row, int column){
    //make sure the square being searched exists on the grid
    assert(row < 10 && row >= 0 &&
           column < 10 && column >= 0);
    //if there is a ship on that square, find out which ship it is
    if(grid.squareStatus[row][column] == SHIP){
        //check each ship in grid's ship array to see if it is on the square
        for(size_t i = 0; i < grid.shipsDeployed; i++){
            //if the ship is vertical
            if(grid.ships[i].isVertical){
                if(grid.ships[i].startColumn == column){
                    if(grid.ships[i].startRow <= row && grid.ships[i].startRow + grid.ships[i].size >= row){
                        return i;
                    }
                }
            }
            //if the ship is horizontal
            else{
                if(grid.ships[i].startRow == row){
                    if(grid.ships[i].startColumn <= column && grid.ships[i].startColumn + grid.ships[i].size >= column){
                        return i;
                    }
                }
            }
        }
        //if no ship is found, return -1
        return -1;
    }
    //if no ship is on that square, return -1
    return -1;
}

// Gets the status of the specified square
// Parameters:
//      grid - a grid struct
//      row - row of the square
//      column - column of the square
// Returns:
//      status of the square
// Possible Errors:
//      asserts that row nad column are within range

SquareStatus GetSquareStatus(const Grid& grid, int row, int column){
    assert(row < 10 && row >= 0 &&
           column < 10 && column >= 0);
    return grid.squareStatus[row][column];
}








