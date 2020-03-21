// Title: Lab 4 - grid.h
//
// Purpose: Declares the functions that manipulate a battleship grid.
//          This Lab 4 version uses a C++ struct to represent a grid
//
// Class: CSC 2430 Winter 2020
// Author: Max Benson

#ifndef BATTLESHIP_GRID_H
#define BATTLESHIP_GRID_H

#include <fstream>

using namespace std;

// Size of grid
const int COUNT_ROWS = 10;
const int COUNT_COLUMNS = 10;

// Maximum number of ships on board
const int SHIPS_MAX = 5;

// Possible states for a square on the grid
// depending on whether a ship occupies it
// or a shot has landed there
enum SquareStatus { WATER, SHIP, MISS, HIT, SUNK };

// Describes a ship and its placement on the grid
//      name - name of ship, its first letter is displayed
//      size - number of squares it occupies
//      isVertical - if true, the ship is positioned vertically, else it's horizontal
//      startRow - row (0-9) of uppermost (if vertical) or leftmost (if horizontal) square it occupies
//      startColumn - column (0-9) of uppermost (if vertical) or leftmost (if horizontal) square it occupies
//      hits - number of different squares that ship occupies that have been hit, it's sunk if hits == size
struct Ship {
    string name;
    int size;
    bool isVertical;
    int startRow;
    int startColumn;
    int hits;
};

// Describes the state of the grid
//      ships - the ships placed on the grid
//      shipsDeployed -- the number of ships that are on the grip (<= SHIPS_MAX)
//      shipsSunk -- the number of ships that have been sunk (game is over if == shipsDeployed)
struct Grid {
    Ship ships[SHIPS_MAX];
    int shipsDeployed;
    int shipsSunk;
    SquareStatus squareStatus[COUNT_ROWS][COUNT_COLUMNS];
};

// Access functions
void Init(Grid& grid);
bool LoadShips(Grid& grid, ifstream& file);
bool SaveShips(const Grid& grid, ofstream& file);

void RandomlyPlaceShips(Grid& grid, const Ship ships[], int countShips);

bool AddShip(Grid& grid, const string& name, int size, bool isVertical, int startRow, int startColumn);
int GetShipsSunk(const Grid& grid);
int GetShipsDeployed(const Grid& grid);
void GetShip(const Grid& grid, int i, Ship& ship);
int FindShip(const Grid& grid, int row, int column);

SquareStatus GetSquareStatus(const Grid& grid, int row, int column);

#endif //BATTLESHIP_GRID_H
