#include "../include/sudoku.h"

// this function takes the input puzzle and create a sudoku which is an array 9x9 and each item is a pointer to a Square
Sudoku *setUpPuzzle(int **puzzle) {
    // allocate memory for the sudoku
    Square ***sudoku = (Square ***)malloc(sizeof(Square **) * ROWS);
    Box **boxes = createBoxes();
    int i, j, w;
    int currBox = 0;

    for (i = 0; i < ROWS; i++) {
        sudoku[i] = (Square **)malloc(sizeof(Square *) * COLS);

        for (j = 0; j < COLS; j++) {
            // allocate memory for each square (9*9)
            sudoku[i][j] = (Square *)malloc(sizeof(Square));
            // initialize items of each square
            sudoku[i][j]->number = puzzle[i][j];

            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            // initialize items of each box
            boxes[currBox]->squares[boxes[currBox]->numbers] = sudoku[i][j];
            boxes[currBox]->numbers++;

            // the box point to the square and the square points to the box
            sudoku[i][j]->boxParent = boxes[currBox];

            // initialize possible array to all 1
            for (w = 0; w < ROWS; w++) {
                sudoku[i][j]->possible[w] = 1;
            }

            // update which box i'm currently in (columns)
            if (j == 2 || j == 5) {
                currBox++;
            }
        }
        // return to column 0
        currBox -= 2;

        // update which box i'm currently in (rows)
        if (i == 2 || i == 5) {
            currBox = i + 1;
        }
    }

    // loop through the entire puzzle and set which numbers can't go in a determinate cell
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (sudoku[i][j]->number != 0) {
                sudoku[i][j]->solvable = 0;  // if there is a number it's altready solved
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }
    return createSudoku(sudoku, boxes);
}

// initialize the sudoku
Sudoku *createSudoku(Square ***squares, Box **boxes) {
    Sudoku *sudoku = (Sudoku *)malloc(sizeof(Sudoku));

    sudoku->squares = squares;
    sudoku->boxes = boxes;

    return sudoku;
}

// loop through the row and the column of the Square in the grid and update possible array
int updateSudoku(Square ***sudoku, int row, int col) {
    int i;
    int number = sudoku[row][col]->number;

    // loop through the row of Square
    for (i = 0; i < ROWS; i++) {
        if (sudoku[i][col]->possible[number - 1] == 1) {
            sudoku[i][col]->solvable--;
        }
        // the number of Square can't go in the column, so we chage the possible array
        sudoku[i][col]->possible[number - 1] = 0;
    }

    // loop through the column of Square
    for (i = 0; i < COLS; i++) {
        if (sudoku[row][i]->possible[number - 1] == 1) {
            sudoku[row][i]->solvable--;
        }
        // the number of Square can't go in the row, so we chage the possible array
        sudoku[row][i]->possible[number - 1] = 0;
    }
    return 1;
}

// check if there are solvable squares
int checkPuzzle(Square ***sudoku, Box **boxes) {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (sudoku[i][j]->solvable == 1) {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);

                return 1;
            }
        }
    }

    if (onlyOneBox(sudoku, boxes)) return 1;

    return checkRows(sudoku, boxes);
}

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

// create a dinamic two dimensional array which is the input puzzle
int **createPuzzle() {
    int **puzzle;
    int i, j;
    // In this array there is the sudoku i want to solve. 0 means the cell is empty
    int array[9][9] = {{ 3, 0, 6,   5, 0, 8,    4, 0, 0 },
                       { 5, 2, 0,   0, 0, 0,    0, 0, 0 },
                       { 0, 8, 7,   0, 0, 0,    0, 3, 1 },
                       { 0, 0, 3,   0, 1, 0,    0, 8, 0 },
                       { 9, 0, 0,   8, 6, 3,    0, 0, 5 },
                       { 0, 5, 0,   0, 9, 0,    6, 0, 0 },
                       { 1, 3, 0,   0, 0, 0,    2, 5, 0 },
                       { 0, 0, 0,   0, 0, 0,    0, 7, 4 },
                       { 0, 0, 5,   2, 0, 6,    3, 0, 0 }

    };

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

// print the puzzle
void printPuzzle(Square ***puzzle) {
    int i, j;
    printf(" -----------------------------\n");
    for (i = 0; i < ROWS; i++) {
        printf("|");
        for (j = 0; j < COLS; j++) {
            if (puzzle[i][j]->number == 0) {
                printf(" _ ");
            } else {
                printf(" %d ", puzzle[i][j]->number);
            }

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
