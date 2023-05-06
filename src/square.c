#include "../include/sudoku.h"

// takes a single square and find what number goes into it
int solveSquare(Square *square) {
    int i;

    // loop through possible array and find the only 1
    for (i = 0; i < ROWS; i++) {
        if (square->possible[i] == 1) {
            // assign a nomber to the square and decrement the unsolved cells
            square->number = i + 1;
            square->solvable = 0;
            UNSOLVED--;
        }
    }
    return 1;
}

