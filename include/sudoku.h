#ifndef SUDOKU_H
#define SUDOKU_H
#define ROWS 9
#define COLS 9

#include <stdio.h>
#include <stdlib.h>

extern int UNSOLVED; //variable declared in sudoku.c
// each boxi is a square 3x3 of the sudoku
typedef struct Box {

} Box;
// each square is a nuber of the sudoku
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
    Box *boxParent;  // which box the cell belongs to

} Square;

Square ***setUpPuzzle(int **puzzle);
int **createPuzzle();
void printPuzzle();

#endif