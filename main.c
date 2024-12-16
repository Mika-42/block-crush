#include <stdio.h>
#include "grid.h"

void initGame(void) {

}

void runGame(void) {

}

int main(void) {
    srand(time(NULL));
    printf("Hello, World try the game!\n");

    Grid grid = {3, 3};

    gridAlloc(&grid);
    gridFill(&grid);
    gridClear(&grid, 0, 2);
    gridClear(&grid, 1, 2);
    gridFallElement(&grid);

    gridPrint(&grid);
    gridFree(&grid);
    return 0;
}
