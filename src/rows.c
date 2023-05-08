#include "../include/sudoku.h"

// this function find numbers that fits in the row
int checkRows(Square*** sudoku, Box** boxes) {
    int i, j, k;
    int count[9];  // count how many times a number can fits in a row
    int col[9];    // if count = 1 stores the index of the number

    for (i = 0; i < ROWS; i++) {
        for (k = 0; k < BOX_NUM; k++) {
            count[k] = 0;
            col[k] = 0;
        }

        for (j = 0; j < COLS; j++) {
            // if a number isn't 0 i ignore it
            if (sudoku[i][j]->number != 0) {
                continue;
            }

            // check possible array of each square
            for (k = 0; k < BOX_NUM; k++) {
                if (sudoku[i][j]->possible[k] == 1) {
                    count[k]++;
                    col[k] = j;
                }
            }
        }

        // check count array if there are some 1
        for (j = 0; j < BOX_NUM; j++) {
            if (count[j] == 1) {
                sudoku[i][col[j]]->number = j + 1;
                sudoku[i][col[j]]->solvable = 0;
                UNSOLVED--;

                updateSudoku(sudoku, i, col[j]);
                updateBoxes(sudoku, i, col[j]);

                return 1;
            }
        }
    }

    return 0;
}