#include "../include/sudoku.h"

int UNSOLVED = ROWS * COLS;  // 81 (9x9) unsolved squares


int main() {
    system("clear");
    int** puzzle;
    Square*** sudoku;
    int i;
    puzzle = createPuzzle();

    sudoku = setUpPuzzle(puzzle);

    printPuzzle(sudoku);

    checkPuzzle(sudoku);

    printf("\n");
    for(i = 0; i<30; i++){
        printf("~");
    }
    printf("\n\n");
    

    printPuzzle(sudoku);

    return 0;
}
