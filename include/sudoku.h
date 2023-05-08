#ifndef SUDOKU_H
#define SUDOKU_H
#define ROWS 9
#define COLS 9
#define BOX_NUM 9

#include <stdio.h>
#include <stdlib.h>

extern int UNSOLVED;  // variable declared in sudoku.c

// rapresents the sudoku with squares (9*9) and boxes(3*3)
typedef struct Sudoku {
    struct Square*** squares;
    struct Box** boxes;
} Sudoku;

typedef struct Square {
    int number;  // number stored into the cell
    int row;
    int column;

    // determinate if a number fits into the cells that are empty, 1 if it fits, 0 if it does't fit
    int possible[9];
    /*
    rapresents how many numbers can fit into the cell, every time i discover a new number i decrement the variable by 1
    when solvable is equal to 1 there will be only one number that can fits.
    */
    int solvable;
    struct Box* boxParent;  // which box the cell belongs to

} Square;

// each box is a square 3x3 of the sudoku
typedef struct Box {
    Square** squares;  // takes track of the numbers inside the box (it's an array of 9 squares)
    int numbers;       // how many numbers are in the box
    int possible[9];   // the same thing that is in Square
    int solvable;
} Box;

// each square is a number of the sudoku

// SQUARE FUNCTIONS
int** createPuzzle();
void printPuzzle(Square*** puzzle);
int checkPuzzle(Square*** sudoku, Box** boxes);
int solveSquare(Square* square);

// SUDOKU FUNCTIONS
Sudoku* createSudoku(Square*** squares, Box** boxes);
Sudoku* setUpPuzzle(int** puzzle);
int updateSudoku(Square*** sudoku, int row, int column);
int checkRows(Square*** sudoku, Box** boxes);

// BOX FUNCTIONS
Box** createBoxes();
int updateBoxes(Square*** sudoku, int row, int col);
int onlyOneBox(Square*** sudoku, Box** boxes);

#endif
