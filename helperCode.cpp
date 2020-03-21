// Title: Lab 4 - helperCode.cpp
//
// Purpose: Implements several helper functions used by the main program to test the grid ADT
//          This Lab 4 version uses a C++ struct to represent a grid
//
// Class: CSC 2430 Winter 2020
// Author: Max Benson
//

#include <iostream>
#include <sstream>
#include <assert.h>
#include "helperCode.h"

// Print the current state of a grid.
// Parameters:
//      grid - a grid struct
// Returns:
//      nothing
//  Possible Errors:
//      none
void PrintGrid(const Grid& grid) {
    int shipCount;

    shipCount = GetShipsDeployed(grid);
    cout << "Number of ships: " << shipCount << endl;
    for (int i = 0; i < shipCount; i ++ ){
        Ship ship;

        GetShip(grid,i, ship);
        cout << "Ship #" << i << ":";
        cout << "  name = " << ship.name;
        cout << ",\tsize = " << ship.size;
        cout << ",  isVertical = " << ship.isVertical;
        cout << ",  startRow = " << ship.startRow;
        cout << ",  startColumn = " <<  (char)('A'+ship.startColumn);
        cout << ",  hits = " << ship.hits << endl;
    }

    // Display the grid
    cout << " 0123456789" << endl;
    for (int row = 0; row < COUNT_ROWS; row ++ ) {
        ostringstream osstrm;
        string line;

        osstrm << row;
        line = osstrm.str();
        for (int column = 0; column < COUNT_COLUMNS; column ++) {
            int i;
            SquareStatus squareStatus;
            Ship ship;

            squareStatus = GetSquareStatus(grid, row, column);
            switch(squareStatus) {
                case WATER:
                    line += ' ';
                    break;
                case SHIP:
                    i = FindShip(grid, row, column);
                    if (i >= 0) {
                        GetShip(grid, i, ship);
                        line += ship.name[0];
                    }
                    else {
                        assert(false);
                    }
                    break;
                case MISS:
                    line += 'X';
                    break;
                case HIT:
                    line += '#';
                    break;
                case SUNK:
                    line += '@';
                    break;
                default:
                    assert(false);
                    break;
            }
        }
        cout << line << endl;
    }
}

