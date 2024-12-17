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
        grid->data = (char *) NULL;
        return TETRIS_SUCCESS;
    }
    return TETRIS_FREE_DYNAMIC_ALLOCATION_FAILED;
}

void gridFill(const Grid *grid) {
    for (ui32 i = 0; i < grid->rows; ++i) {
        for (ui32 j = 0; j < grid->columns; ++j) {
            const char *letter = "HOAX";
            grid->data[i * grid->columns + j] = letter[rand() % 4];
        }
    }
}

void gridPrint(const Grid *grid) {
    for (ui32 i = 0; i < grid->rows; ++i) {
        printf("\n");
        for (ui32 j = 0; j < grid->columns; ++j) {
            printf("%c", grid->data[i * grid->columns + j]);
        }
    }
}

ErrorCode gridEmptyBox(const Grid *grid, ui32 rows, ui32 columns) {
    if (grid == NULL || grid->data == NULL) {
        return TETRIS_DYNAMIC_ALLOCATION_FAILED;
    }
    if (rows >= grid->rows || columns >= grid->columns) {
        return TETRIS_GRID_SIZE_ERROR;
    }

    grid->data[rows * grid->columns + columns] = ' ';
    return TETRIS_SUCCESS;
}

void gridFallElement(const Grid *grid) {
    // on s'arrete une ligne avant pour ne pas chercher
    // le voisin du dessous de la dernière ligne
    for (ui32 i = 0; i < grid->rows - 1; ++i) {
        for (ui32 j = 0; j < grid->columns; ++j) {

            // si la case actuelle n'est pas vide mais la case en dessous l'est
            // alors on permute les deux cases
            if (!isEmptyBox(grid, i, j) && isEmptyBox(grid, i, j + 1)) {
                swapBoxes(grid, i, j, i+1, j);
            }
        }
    }
}

bool isEmptyBox(const Grid *grid, const ui32 row, const ui32 column) {
    return grid->data[row * grid->columns + column] == ' ';
}

ErrorCode swapBoxes(const Grid* grid, const ui32 row1, const ui32 column1, const ui32 row2, const ui32 column2)
{
    if (grid == NULL || grid->data == NULL) {
        return TETRIS_DYNAMIC_ALLOCATION_FAILED;
    }
    if(row1 >= grid->rows || column1 >= grid->columns) {
        return TETRIS_GRID_SIZE_ERROR;
    }
    if(row2 >= grid->rows || column2 >= grid->columns) {
        return TETRIS_GRID_SIZE_ERROR;
    }

    char* box1 = &grid->data[row1 * grid->columns + column1];
    char* box2 = &grid->data[row2 * grid->columns + column2];

    const char temp = *box1;
    *box1 = *box2;
    *box2 = temp;

    return TETRIS_SUCCESS;
}

// bool neighbourIsSameTop(const Grid *grid, const ui32 row, const ui32 column) {
//     const ui32 legalIndex = (column - 1) * grid->columns + row;
//
//     // vérifier que l'on accède pas à une valeur hors de la grille
//     if (legalIndex >= grid->rows) {
//         return false;
//     }
//     return grid->data[column * grid->columns + row] == grid->data[legalIndex];
// }
//
// bool neighbourIsSameBottom(const Grid *grid, const ui32 row, const ui32 column) {
//     const ui32 legalIndex = (column + 1) * grid->columns + row;
//
//     // vérifier que l'on accède pas à une valeur hors de la grille
//     if (legalIndex >= grid->rows) {
//         return false;
//     }
//     return grid->data[column * grid->columns + row] == grid->data[legalIndex];
// }
//
// bool neighbourIsSameLeft(const Grid *grid, const ui32 row, const ui32 column) {
//     const ui32 legalIndex = column * grid->columns + (row - 1);
//
//     // vérifier que l'on accède pas à une valeur hors de la grille
//     if (legalIndex >= grid->rows) {
//         return false;
//     }
//     return grid->data[column * grid->columns + row] == grid->data[legalIndex];
// }
//
// bool neighbourIsSameRight(const Grid *grid, const ui32 row, const ui32 column) {
//     const ui32 legalIndex = column * grid->columns + (row + 1);
//
//     // vérifier que l'on accède pas à une valeur hors de la grille
//     if (legalIndex >= grid->rows) {
//         return false;
//     }
//     return grid->data[column * grid->columns + row] == grid->data[legalIndex];
// }
