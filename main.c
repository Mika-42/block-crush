#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grid.h"

void initGame(void) {
}

void runGame(void) {
}

int main(void) {
	srand(42); //time(nullptr)
	printf("Hello, World try the game!\n");

	Grid grid = {10, 5};

	gridFill(&grid);
	//gridEmptyBox(&grid, (Coordinate){1, 2});

	printf("\nstep 1-----------------------\n");
	gridPrint(&grid);

	removeLongestSequences(&grid);

	printf("\nstep 2-----------------------\n");
	gridPrint(&grid);
	printf("\nstep 3-----------------------\n");
	gridFallElement(&grid);
	gridFallElement(&grid);
	gridPrint(&grid);

	//gridPrint(&grid);

	return 42;
}
