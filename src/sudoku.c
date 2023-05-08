#include "../include/sudoku.h"

int UNSOLVED = ROWS * COLS;  // 81 (9x9) unsolved squares


// this is the main file that calls other funcion to solve the sudoku
int main() {
    system("clear");
    int** puzzle;
    Sudoku* sudoku;
    int i, progress;

    puzzle = createPuzzle();

    sudoku = setUpPuzzle(puzzle);

    printPuzzle(sudoku->squares);

    //call checkPuzzle until is solved
    while (UNSOLVED > 0) {
        progress = checkPuzzle(sudoku->squares, sudoku->boxes);

        //if the program is stuck exit 
        if (progress == 0) {
            printf("\nFailed to solve the puzzle!\n\n");
            break;
        }
    }

    printf("\n\n");
    for (i = 0; i < 30; i++) {
        printf("~");
    }
    printf("\n");
    if(UNSOLVED == 0){
        printf("\n          SOLUTION!!        \n\n");
    }
    
    printPuzzle(sudoku->squares);

    return 0;
}
