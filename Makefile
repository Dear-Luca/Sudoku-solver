sudoku: sudoku.o box.o puzzle.o rows.o 
	gcc sudoku.o box.o puzzle.o rows.o  -o main

box.o: src/box.c include/sudoku.h
	gcc -c src/box.c

puzzle.o: src/puzzle.c include/sudoku.h
	gcc -c src/puzzle.c

rows.o: src/rows.c include/sudoku.h
	gcc -c src/rows.c

sudoku.o: src/sudoku.c include/sudoku.h
	gcc -c src/sudoku.c

clean:
	rm *.o sudoku