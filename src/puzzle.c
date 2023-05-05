#include "sudoku.h"

//this function takes the input puzzle and create a sudoku which is an array 9x9 and each item is a pointer to a Square
Square*** setUpPuzzle(int **puzzle){
    //allocate memory for the sudoku
    Square*** sudoku = (Square***)malloc(sizeof(Square**)*ROWS);
    int i,j,w;
    for(i=0; i<ROWS; i++){
        sudoku[i] = (Square**)malloc(sizeof(Square**)*COLS);
        for(j = 0; j<COLS; j++){
            //allocate memory for each square (9*9)
            sudoku[i][j] = (Square*)malloc(sizeof(Square));

            sudoku[i][j]->number = puzzle[i][j];

            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;

            //initialize possible array to all 0
            for(w = 0; w<ROWS; w++){
                sudoku[i][j]->possible[w] = 0;
            }            
        }
    }
    //loop through the entire puzzle and set which numbers can't go in a determinate cell
    for(i = 0; i<ROWS; i++){
        for(j = 0; j<COLS; j++){
            if(sudoku[i][j]->number != 0){
                sudoku[i][j]->solvable = 0; //if there is a number it's altready solved
                updateSudoku(sudoku, i, j);
                UNSOLVED--;
                
            }
        }
    }


}
//loop through the row and the column of the Square in the grid and update possible array
int updateSudoku(Square*** sudoku, int row, int col){
    int w;
    int number = sudoku[row][col]->number;
    //loop through the row of Square
    for(w = 0; w<ROWS; w++){
        if(sudoku[w][col]->possible[number-1] == 1){
            sudoku[w][col]->solvable--;
        }
        //the number of Square can't go in the column, so we chage the possible array
        sudoku[w][col]->possible[number-1] = 0;
    }
    //loop through the column of Square
    for(w=0; w<COLS; w--){
        if(sudoku[row][w]->possible[number-1] == 1){
            sudoku[w][col]->solvable--;
        }
        //the number of Square can't go in the row, so we chage the possible array
        sudoku[w][col]->possible[number-1] = 0;
    }
    return 1;
}

//create a dinamic two dimensional array which is the input puzzle
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

//print the puzzle
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
 