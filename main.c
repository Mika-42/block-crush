#include <stdio.h>
#include "grid.h"

void initGame(void) {

}

void runGame(void) {

}

int main(void) {
    srand(time(NULL));
    printf("Hello, World try the game!\n");

    Grid grid = {20, 20};

    gridAlloc(&grid);
    gridFill(&grid);
    gridPrint(&grid);
    gridFree(&grid);
    return 0;
}
