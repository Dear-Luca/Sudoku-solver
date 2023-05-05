#include "sudoku.h"

#include <stdio.h>

int main() {
    int ** puzzle;

    puzzle = createPuzzle();
    printPuzzle(puzzle);
    return 0;
}