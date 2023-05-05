#include "sudoku.h"

int UNSOLVED = ROWS*COLS; //81 (9x9) unsolved squares

int main() {
    int** puzzle;
    Square*** sudoku;  // main variable that rapresents the sudoku
    puzzle = createPuzzle();
    printPuzzle(puzzle);
    setUpPuzzle(puzzle);
    return 0;
}