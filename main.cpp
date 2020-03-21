// Title: Lab 4 - main.cpp
//
// Purpose: Program for testing the Battleship "grid" ADT.
//
// Class: CSC 2430 Winter 2020
//
// Author: Max Benson and Andrew McLain
//
#include <iostream>
#include "grid.h"
#include "helperCode.h"

//Forward declarations
void ManuallyPlaceShips(Grid& grid, const Ship ships[], int countShips);
bool LoadShipsOnGrid(const string& fileName, Grid &grid);
bool SaveShipsOnGrid(const string&fileName, const Grid& grid);

//
// Main program:
//
// This program exercises the grid functions implemented in this lab.  It starts by offering the user the choice
// whether to 1) randomly place ships on the grid, 2) manually place ships on a grid, or 3) Load from file
//
// After ships have been placed on the grid, it prints the configuration.
//
// Finally it gives the user a chance to save the grid to a file
//
int main() {
    string command;
    Ship   shipsToPlace[] =  { { "Submarine", 3 },
                                        { "Battleship", 4 },
                                        { "Destroyer",  3 },
                                        { "PatrolBoat", 2 },
                                        { "Carrier",    5 } };
    Grid grid;


    // Determine how ships should be placed
    do {
        cout << "Enter M to manually place ships, R to randomly place ships, L to load from file: ";
        cin >> command;
    } while (command != "M" && command != "R" && command != "L");

    // Place the ships on the grid
    if (command == "M") {
        ManuallyPlaceShips(grid, shipsToPlace, sizeof(shipsToPlace)/sizeof(shipsToPlace[0]));

        // Print the ships to verify correctness
        PrintGrid(grid);
    }
    else if (command == "R") {
        int randomSeed;

        // Prompt for random seed to use
        cout << "Enter seed for random number generator: ";
        cin >> randomSeed;
        srand(randomSeed);

        // Do the random placement
        RandomlyPlaceShips(grid, shipsToPlace, sizeof(shipsToPlace)/sizeof(shipsToPlace[0]));

        // Print the ships to verify correctness
        PrintGrid(grid);
    }
    else if (command == "L") {
        string fileName;

        // Get the file name to load
        cout << "File name: ";
        cin >> fileName;
        if (LoadShipsOnGrid(fileName, grid)) {
            // Print the ships to verify correctness
            PrintGrid(grid);
        }
    }


    // Save configuration if desired (but not when we just loaded from file)
    if (command != "L") {
        do {
            cout << "Do you want to save the configuration? (Y/N): ";
            cin >> command;
        } while (command != "Y" && command != "N");

        if (command == "Y") {
            string fileName;

            // Get the file name to load
            cout << "File name: ";
            cin >> fileName;

            SaveShipsOnGrid(fileName, grid);
        }
    }
    return 0;
}

// This function prompts the user for the desired location for each of the five ships
//      So long as a ship placement does not extend outside the grid or overlap previous
//      ships that have been added the ship will be placed as the user specifies.  Otherwise
//      the user will be asked again until a acceptable placement is enter.
//  Parameters:
//      grid - a grid
//      ships - the array of ships to be placed
//      countShips - number of ships in the array
//  Returns:
//      nothing
//  Possible Errors:
//      none
void ManuallyPlaceShips(Grid& grid, const Ship ships[], int countShips) {
    Init(grid);
    for (int i = 0; i < countShips; i ++ ) {
        bool firstTime;
        int isVertical;
        int startRow;
        int startColumn;
        string command;

        do {
            cout << "Do you want to print the grid? (Y/N): ";
            cin >> command;
        } while(command != "Y" && command != "N");
        if (command == "Y") {
            PrintGrid(grid);
        }

        firstTime = true;
        do {
            string hOrV;

            // If we are retrying print message
            if (!firstTime) {
                cout << "Ship could not be added, please try again." << endl;
            }
            else {
                firstTime = false;
            }

            // Ask user where to place the ship
            do {
                cout << "Place your " << ships[i].name << " horizontally or vertically?  Enter H or V: ";
                cin >> hOrV;
            } while( hOrV != "H" && hOrV != "V");
            isVertical = (hOrV == "V");

            if (isVertical) {
                cout << "Enter row and column of upper end of ship as numbers: ";
            }
            else {
                cout << "Enter row and column of left end of ship as numbers: ";
            }
            cin >> startRow >> startColumn;
        } while( !AddShip( grid, ships[i].name, ships[i].size, isVertical, startRow, startColumn));
    }
}

// This function saves the ships on a grid to file.  It attempts to open the file
//      given by fileName.
//      -   If it cannot be opened, it prints an appropriate error message and returns.
//      -   If it can be opened it will call the SaveShips interface method
//          to save the ships.  If any error occurs saving the ships, an appropriate error
//          message is printed.  In either case it closes the file and returns.
//  Parameters:
//      fileName - name of file to save to
//      grid - a grid
//  Returns:
//      true if no errors, false otherwise
//  Possible Errors:
//      error opening the file
//      file write error

bool SaveShipsOnGrid(const string&fileName, const Grid& grid){
    ofstream file;
    file.open(fileName);
    //if file cannot open, print error message
    if(!file.is_open()){
        cerr << "Could not open " << fileName;
        return false;
    }
    //if grid cannot be saved to file, print error message
    if(!SaveShips(grid, file)){
        cerr << "Error occurred while saving ships";
        file.close();
        return false;
    }
    file.close();
    return true;
}

// This function loads ships from file and places them on a grid.  It attempts to open the file
//      given by fileName.
//      -   If it cannot be opened, it prints an appropriate error message and returns.
//      -   If it can be opened it will call the LoadShips interface method
//          to load the ships.  If any error occurs loading the ships, an appropriate error
//          message is printed.  In either case it closes the file and returns.
//  Parameters:
//      fileName - name of file to load from
//      grid - a grid
//  Returns:
//      true if no errors, false otherwise
//  Possible Errors:
//      error opening the file
//      file read error

bool LoadShipsOnGrid(const string& fileName, Grid &grid){
    //initialize grid and open file
    Init(grid);
    ifstream file;
    file.open(fileName);
    //if file cannot open, print error message
    if(!file.is_open()){
        cerr << "Could not open " << fileName;
        return false;
    }
    //if grid cannot be properly read from file, print error message
    if(!LoadShips(grid, file)){
        cerr << "Could not load ships ";
        return false;
    }
    file.close();
    return true;
}