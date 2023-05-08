#include "../include/sudoku.h"

Box** createBoxes() {
    int i, j;
    Box** boxes = (Box**)malloc(sizeof(Box*) * BOX_NUM);  // allocate memory for 9 pointers to a Box

    for (i = 0; i < BOX_NUM; i++) {
        boxes[i] = malloc(sizeof(Box));                                // allocate memory for each box
        boxes[i]->squares = (Square**)malloc(sizeof(Square*) * ROWS);  // allocate memory for the squares inside the box
        boxes[i]->numbers = 0;
        boxes[i]->solvable = 9;

        // initialize possible array to all 1 because at the beginnig we don't now if a number fits or it doesn't fit
        for (j = 0; j < BOX_NUM; j++) {
            boxes[i]->possible[j] = 1;
        }
    }

    return boxes;
}

// Funtion that update Boxes
int onlyOneBox(Square*** sudoku, Box** boxes) {
    int i, j, k;
    int count, tmp;  // count how many times a number can fits in a Box
    // loop through boxes to check numbers
    for (i = 0; i < BOX_NUM; i++) {
        // loop through numbers (possible array)
        for (j = 0; j < BOX_NUM; j++) {
            count = 0;

            // loop through squares
            for (k = 0; k < BOX_NUM; k++) {
                if (boxes[i]->squares[k]->number != 0) {
                    continue;  // if the number isn't 0 skip to next iteration
                }

                // if is 0 i want to check if the current number fits into it
                if (boxes[i]->squares[k]->possible[j] == 1) {
                    count++;
                    tmp = k;
                }

                // if a numbers fits more than ones exit the loop and try with another one
                if (count == 2) break;
            }
            // there is only a square that fits the number
            if (count == 1) {
                boxes[i]->squares[tmp]->number = j + 1;
                UNSOLVED--;
                boxes[i]->squares[tmp]->solvable = 0;

                updateSudoku(sudoku, boxes[i]->squares[tmp]->row, boxes[i]->squares[tmp]->column);
                return 1;
            }
        }
    }
    return 0;
}

// the same thing that is in update sudoku but the loop is through each square of the box
int updateBoxes(Square*** sudoku, int row, int col) {
    int i;
    int number = sudoku[row][col]->number;
    Box* box = sudoku[row][col]->boxParent;

    for (i = 0; i < BOX_NUM; i++) {
        // for each numbers in the box i update the possible array of the others
        if (box->squares[i]->possible[number - 1] == 1) {
            box->squares[i]->solvable--;
            // number can't go in this square so i set the possible[n - 1] to 0
            box->squares[i]->possible[number - 1] = 0;
        }
    }

    return 1;
}