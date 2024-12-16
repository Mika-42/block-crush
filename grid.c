//
// Created by Matis on 16/12/2024.
//

#include "grid.h"

#include <stdio.h>

ErrorCode gridAlloc(Grid *grid) {
    if (grid->columns == 0 || grid->rows == 0) {
        return TETRIS_GRID_SIZE_ERROR;
    }
    grid->data = calloc(grid->columns * grid->rows, sizeof(char));
    if (grid->data == NULL) {
        return TETRIS_DYNAMIC_ALLOCATION_FAILED;
    }
    return TETRIS_SUCCESS;
}

ErrorCode gridFree(Grid *grid) {
    if (grid != NULL && grid->data != NULL) {
        free(grid->data);
        grid->data = (char*)NULL;
        return TETRIS_SUCCESS;
    }
    return TETRIS_FREE_DYNAMIC_ALLOCATION_FAILED;
}

void gridFill(const Grid *grid) {
    for(unsigned int i = 0; i < grid->rows; ++i) {
        for(unsigned int j = 0; j < grid->columns; ++j) {
            const char* letter = "AOHX";
            grid->data[i * grid->columns + j] = letter[rand()%4];
        }
    }
}

void gridPrint(Grid *grid) {
    for(unsigned int i=0;i<grid->rows;++i) {
        printf("\n");
        for(unsigned int j=0;j<grid->columns;++j) {
            printf("%c",grid->data[i * grid->columns + j]);
        }
    }
}
