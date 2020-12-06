# LAB 4 - Battleship Game, Part 1 - Ship Placement
## Goal
Begin a three part series of labs where you will implement the class Battleship game (https://en.wikipedia.org/wiki/Battleship_(game)).  When you finish the final lab of this sequence, you will be able to play against the computer as pictured below:

![Lab 6 Screen Shot](/image1.png)

In this lab you will do an initial implementation of a `Grid` ADT which will maintain the location and status of this ships that a player has placed on the grid. The main new C++ concept that you will get to practice is working with two dimensional arrays.

## Sample Run

In this first lab we will simplify things by not using a graphical display.  Instead, you'll use a command line user interface for testing placing ships on the grid.  This interface will offer three options - manual placement of ships,  random placement of ships, and loading a ship configuration from a file.  After placement is completed in the manual or random options, you will be prompted to save the ship placement to a file, if desired.

The following screen shot shows a run where random ship placement was chosen:

![Random Ship Placement](/image5.png)

As you can see, when random ship placement is chosen, the user has to enter an integer for a "random seed."  Different random seeds will usually give you different ship placements, but you get the same sequence of random numbers if you enter the same seed each time.  Random ship placement makes the game more fun, but repeatability makes testing easier!

Next, here's a screen shot for the first part of a run where manual ship placement was chosen:

![Manual Ship Placement1](/image3.png)

If the user tries to enter a ship placement which doesn't fit within the 10x10 grid, or overlaps a ship that has already been placed on the grid, no placement is done.  No changes to the `Grid` data structure should be made in these error situations.  It's important that the user can continue on and try finishing adding ships.  The following screen shot shows an example of cases where the user tried to  add ships that would have extended outside the grid or overlap another ship.

![Manual Ship Placement2](/image2.png)

## Files you are given
In this lab, you are given all the files you will need for your CLion project.  

* **CMakeLists.txt** - This contains the information necessary to build the project.  This file should not be modified.

* **main.cpp** – This file contains the main routine which drives the command line user interface, and two functions `ManuallyPlaceShips` and `TestSaveLoad`.  The main routine and `ManuallyPlaceShips` have been implemented for you and should not be modified.  You are required to implement `TestSaveLoad`. Doing so will give you more practice working with input and output file streams.

* **helperCode.h** – This file declares two functions implemented in **helperCode.cpp**.  This file has been completed for you and should not be modified.

* **helperCode.cpp** – This file implements the useful functions `PrintGrid` and `CompareGridConfigurations` which are called by the main program.  This file has been completed for you and should not be modified.

* **grid.h** – This file contains the declaration of the `Grid` ADT and the interface functions that used to manipulate the grid.  This file has been completed for you and should not be modified.
.
* **grid.cpp** – This is the file where you will do most of your work.   The `#include` lines that you will need have been added, as well as header comments for each of the interface function.  You will need to fix the file header comment, and implement the ten interface functions.

##	The `Grid` ADT

A `struct` is used to group the information about the grid into a single “package.”  

```
struct Grid {
    Ship ships[SHIPS_MAX];
    int shipsDeployed;
    int shipsSunk;
    SquareStatus squareStatus[COUNT_ROWS][COUNT_COLUMNS];
};
```
As you can see it stores an array of `Ship` called `ships`, where `Ship` is specified by:

```
// Describes a ship and its placement on the grid
//      name -       name of ship, its first letter is displayed
//      size -       number of squares it occupies
//      isVertical - if true, the ship is positioned vertically, else it's horizontal
//      startRow -   row (0-9) of uppermost (if vertical) or leftmost (if horizontal) square
//		     it occupies
//      startColumn -column (0-9) of uppermost (if vertical) or leftmost (if horizontal) square
//		     it occupies
//      hits -       number of different squares that ship occupies that have been hit, it's sunk if
//		     hits == size
struct Ship {
    string name;
    int size;
    bool isVertical;
    int startRow;
    int startColumn;
    int hits;
};
```
In addition, it stores the count of ships that have been placed on the grid in the `shipsDeployed` member, and the number of these ships which have already been sunk in the `shipsSunk` member.  In this lab `shipsSunk` will always be zero.  The `squareStatus` member is a two-dimensional array that keeps track of the status of each square of the grid.  In this lab each square will either be marked as `WATER` or `SHIP`, but in future labs, it could also be marked as `MISS`, `HIT`, or `SUNK`.
  .
The `Grid` ADT interface functions that you will implement in this lab are:

```
// Initialize the grid struct
void Init(Grid& grid);

// Read the ship configuration for a grid from a text file stream
bool LoadShips(Grid& grid, ifstream& file);

// Save the ship configuration for a grid to a text file stream
bool SaveShips(const Grid& grid, ofstream& file);

// Randomly place the indicated ships on an empty grid.
void RandomlyPlaceShips(Grid& grid, const Ship ships[], int countShips);

// Attempt to place a ship on the grid with the specified orientation and start position
bool AddShip(Grid& grid, const string& name, int size, bool isVertical, int startRow, int startColumn);

// Returns the number of ships that have been sunk
int GetShipsSunk(const Grid& grid);

// Returns the number of ships placed on the grid
int GetShipsDeployed(const Grid& grid);

// Retrieves information about the i-th ship
void GetShip(const Grid& grid, int i, Ship& ship);

// Determines if there is a ship covering the specified square.  
int FindShip(const Grid& grid, int row, int column);

// Gets the status of the specified square
SquareStatus GetSquareStatus(const Grid& grid, int row, int column);
```
The function header comments in the file **grid.cpp** give more details about what each of these functions should do.  Some of them (`Init`, `GetShipsSunk`, `GetShipsDeployed`, `GetShip`, `GetSquareStatus`) are very simple, and should not take you much time to write.

## Recommended implementation order

You will need to write the ten `Grid` interface functions in **grid.cpp** and the function TestSaveLoad in **main.cpp**.  Here is a suggested order of implementation.

1.	Make sure you put your name in the file headers for **main.cpp** and **grid.cpp** as co-author.
2.	Stub out all ten `Grid` interface functions.  That means, add the function to **grid.cpp**.  Each function body should initially contain the line
```
assert(false);
```
You will remove this line when you implement the function.  The point of this line is to warn you that the function hasn’t been implemented if it gets called.

3.	Build your understanding of the `Grid` ADT by implementing the following interface functions:

```
void Init(Grid& grid);
int GetShipsSunk(const Grid& grid);
int GetShipsDeployed(const Grid& grid);
void GetShip(const Grid& grid, int i, Ship& ship);
SquareStatus GetSquareStatus(const Grid& grid, int row, int column);
```

  None of these functions require any conditional logic.  Only `Init` requires loops.  Once you are clear what they do they should be easy to implement.

  It is a good programming practice to check the validity of the parameters `i`, `row`, and `column` when present.  Use assert statements to verify that they make sense, e.g. assert that `i` is non-negative and less than the number of ships deployed, assert that `row` is non-negative and less than `COUNT_ROWS`, and assert that `column` is non-negative and less than `COUNT_COLUMNS`.

4.	Next focus on getting manual ship placement working.  The command line interface provided for you will make it easy for you to test things, but you are going to have to implement the following functions before you can run it:

```
bool AddShip(Grid& grid, const string& name, int size, bool isVertical, int startRow, int startColumn);
int FindShip(const Grid& grid, int row, int column);
```

  *	When adding a ship, you need to make sure three things are true:
      *	You have room for another ship in the array
      *	The ship’s placement fits within the `COUNT_ROWS` x `COUNT_COLUMNS` grid
      *	The ship’s placement would not overlap a ship already placed on the grid.

  If any of these things fail to be true, you should return `false`.  Make sure you do **NOT** modify the grid struct

  *	When implementing both functions, don’t forget to handle the cases when `isVertical` is `true`, and when `isVertical` is `false`.

  * Once you have these functions implemented, use the manual ship placement interface to make sure that the ship displays properly on the grid after you add it.  You should see the ship displayed along with the first letter of the name of the ship.  You also MUST test that that `AddShip` returns `false` when you specify a placement that would extend outside the grid or overlap a ship.  

5.	Now get random placement of ships working.  For this you need to implement:

```
void RandomlyPlaceShips(Grid& grid, const Ship ships[], int countShips);
```

For each ship, you will use the `rand()` library function to generate random values for `isVertical`, `startRow`, and `startColumn` and then call `AddShip`.  If `AddShip` returns `false`, then keep retrying, generating new sets of random values until it returns true.

Note: to get a random `bool` value, use the expression `rand() % 2`, to get a random value for row use the expression `rand() % COUNT_ROWS`, etc.
.  

6.	The final step is to get load and save working.  Start by writing `SaveShips`. Here’s an example of what it should write to file stream:

```
5
Submarine
3 1 0 0
Battleship
4 0 9 0
Destroyer
3 0 3 3
PatrolBoat
2 1 4 4
Carrier
5 1 4 5
```

The first line gives the number of ships.  Then for each ship, two lines are output.  The first of these two lines gives the ship’s `name`.  The second line has the values for `size`, `isVertical`, `startRow`, and `startColumn`.  The function returns `true` if no errors occur on the file stream, otherwise `false`.

Then, in **main.cpp**, implement `SaveShipsOnGrid`.  This function will attempt the open the file specified by the `fileName` parameter.  If it cannot open the file, it should print an appropriate error message and return `false`.  Else, it should call the `SaveShips` interface function.  It should then close the file, and return `true` or `false` depending on the return value of `SaveShips`.

Test your save routines by doing a manual or random placement of ships, and selecting the save option.  View the contents of the file that was produced to see if it is correct.

Then you are ready to implement  `LoadShips`.  If errors occur reading information from the file, or `AddShip` returns `false`, you should print an informative error message.

Finally you should implement `LoadShipsOnGrid` in **main.cpp**.  This function is very similar to `SaveShipsOnGrid`, except you are opening an input file stream.

At minimum, you should test your load functionality using the provided files **saveTest1.txt**, **saveTest2.txt**, **saveTest3.txt**, **saveOther.txt**, and **tooMany.txt**.  Make sure it handles the case of trying to load a file that does not exist gracefully.


## Testing

Make sure you test your code thoroughly.  
* Check that your random placement agrees with the screen shot when 1 is entered as a random seed, and try other seeds as well.
* For manual ship placement, make sure you test both ship orientations in situations where they can be placed or they cannot be placed because they would extend outside the grid or overlap a ship that already has been placed.
* Examine the contents of the file produced when you save the configuration to file.  
* Make sure saving fails when you give an invalid file name.  
* Write a quick test program to make sure loading fails when the file isn't formatted correctly.
* Your file output should be **identical** to the output that is provided to you.

## Style

Your program needs to be orderly and readable.  If you are working a development team and don’t write clean looking code, you will be unpopular among your colleagues and may not work on that team very long.  Because of this your program will be graded on style as well as correctness.  Please refer to the style guidelines discussed in class and in reading assignments concerning

  *	Indention of code
  *	Consistent use of {}, preferably Stroustrup style
  *	Meaningful names of identifiers
  *	Naming conventions for identifiers (camelCase for variables, CamelCase for function names. First word of a function name typically should be a verb.)
  *	No use of global variables. Global variables sometimes are appropriate, but not in the assignments we will be giving this quarter.
  *	Making sure *struct* and object parameters are passed by reference (and declared const if appropriate)

Do NOT violate the ADT encapsulation.  Only the functions declared in **grid.h** should access the fields and array elements of the `Grid` structure.

## Documentation

At the start of your file you should have a header comment that gives the title of the assignment, the purpose, and your name.  Here is an example (from Lab 1) of what that could look like:

      ```
      /*
          Title:      Lab 1 – evalSteps.cpp
          Purpose:    implement the GetEvalSteps functions called by the main program to generate the evaluation
                      steps for an expression passed in as a parameter.
          Author:     Sally Johnson
          Date:       January 6, 2020
      */
      ```
Each subordinate function should also start with a header that describes what it does, it’s parameters, what it returns, and how errors are handled.  Here is an example (again from Lab 1):

    ```
    // Produce a string of evaluation steps for simplifying an expression
    // For example:
    //      if “2+3*4-5”  is passed to this function, the string “2+3*4-5 = 2+12-5\n        = 14-5\n        = 9”
    //      would be returned
    // Parameters:
    //      expression - an arithmetic expression
    // Returns:
    //      a string consisting of the evaluation steps needed to simplify the expression
    // Possible Error Conditions:
    //      If evaluating the expression causes division by zero, this function crash.
    //      If evaluating the expression causes an oveflow, the results may not be reliable.
    ```

You should include additional comments in your code to describe what you are doing.   If it is hard to understand what a variable is for, add a comment after it.   It possible, though, to put in too many comments, so be judicious and make sure you have time left to do well in your other classes when it comes to commenting.

## Submitting your code
Your solution should be contained within files that were provided.  You MUST NOT modify the main routine, **CMakeFiles.txt**, **helperCode.h**, **helperCode.cpp**, or  **grid.h**.  Do not modify the main routine or the routine `ManuallyPaceShips`.

Make sure you test your code thoroughly.  We will try your code with our own test files, and we will programmatically test your `Grid` ADT with our own test program.  

You will need to push your last version of your program before the lab deadline. As a good programming practice remember to commit frequently and to push every time you have a functioning version of your code.

## Grading
Correctness is essential.  Make sure your solution builds as described above and correctly handles the test cases displayed in the screen shot.  We will test on other input values as well. Your code must compile and should not have runtime errors (crash).

Even if your solution operates correctly, points will be taken off for:
- Not following the design described above
- Not adhering to style guidelines described above
- Using techniques not presented in class
- Programming error not caught by other testing
- Not following good programming practices

## Academic Integrity
This programming assignment is to be done on an individual basis. At the same time, it is understood that learning from your peers is valid and you are encouraged to talk among yourselves about programming in general and current assignments in particular.  Keep in mind, however, that each individual student must do the work in order to learn.  Hence, the following guidelines are established:
- Feel free to discuss any and all programming assignments but do not allow other students to look at or copy your code. Do not give any student an electronic or printed copy of any program you write for this class.
- Gaining the ability to properly analyze common programming errors is an important experience. Do not deprive a fellow student of his/her opportunity to practice problem solving: control the urge to show them what to do by writing the code for them.
- If you’ve given the assignment a fair effort and still need help, see the instructor or a lab assistant.
- **If there is any evidence that a program or other written assignment was copied from another student, neither student will receive any credit for it. This rule will be enforced.**
- Protect yourself: Handle throw-away program listings carefully, keep your repository private.

Refer to the ECS Department Policy on Academic Integrity that is included in the class syllabus.

## Grading Rubric Summary
The following aspects are going to be consider during grading. Make sure you comply with all of them.
- The program compiles (there will be no partial credit for programs that do not compile)
- Provides the correct output for the test cases
- Catches errors gracefully, the program does not crash on incorrect input
- The program outputs the information in the specified format
- The assignment follows all the instructions
- In general the program does not crash
