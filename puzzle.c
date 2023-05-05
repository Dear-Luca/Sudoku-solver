#include "sudoku.h"
#define ROWS 9
#define COLS 9
int **createPuzzle() {
    int **puzzle;
    int i, j;
    // In this array there is the sudoku i want to solve. 0 means the cell is empty
    int array[ROWS][COLS] = {0, 1, 9, 0, 0, 2, 0, 0, 0,
                             4, 7, 0, 6, 9, 0, 0, 0, 1,
                             0, 0, 0, 4, 0, 0, 0, 9, 0,

                             8, 9, 4, 5, 0, 7, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 2, 0, 1, 9, 5, 8,

                             0, 5, 0, 0, 0, 6, 0, 0, 0,
                             6, 0, 0, 0, 2, 8, 0, 7, 9, 
                             0, 0, 0, 1, 0, 0, 8, 6, 0};

    // allocate memory for the puzzle, array of int*
    puzzle = (int **)malloc(sizeof(int *) * ROWS);
    for (i = 0; i < ROWS; i++) {
        // loop throught rows and allocate memory for each col, array of int
        puzzle[i] = (int *)malloc(sizeof(int) * COLS);

        for (j = 0; j < COLS; j++) {
            puzzle[i][j] = array[i][j];
        }
    }
    return puzzle;
}

void printPuzzle(int **puzzle) {
    system("clear");
    int i, j;
    printf(" -----------------------------\n");
    for (i = 0; i < ROWS; i++) {
        printf("|");
        for (j = 0; j < COLS; j++) {
            printf(" %d ", puzzle[i][j]);
            if (((j + 1) % 3) == 0) {
                printf("|");
            }
        }
        printf("\n");
        if (((i + 1) % 3) == 0) {
            printf(" -----------------------------\n");
        }
    }
}
 