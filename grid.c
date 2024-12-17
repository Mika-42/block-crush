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
    for (unsigned int i = 0; i < grid->rows; ++i) {
        for (unsigned int j = 0; j < grid->columns; ++j) {
            const char *letter = "HOAX";
            grid->data[i * grid->columns + j] = letter[rand() % 4];
        }
    }
}

void gridPrint(const Grid *grid) {
    for (unsigned int i = 0; i < grid->rows; ++i) {
        printf("\n");
        for (unsigned int j = 0; j < grid->columns; ++j) {
            printf("%c", grid->data[i * grid->columns + j]);
        }
    }
}

ErrorCode gridEmptyBox(const Grid *grid, unsigned int rows, unsigned int columns) {
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
    for (unsigned int i = 0; i < grid->rows - 1; ++i) {
        for (unsigned int j = 0; j < grid->columns; ++j) {
            // poisition x, y d'une case
            const unsigned int index = i * grid->columns + j;

            // position x, y de la case en dessous
            const unsigned int nextIndex = (i + 1) * grid->columns + j;

            // si la case actuelle n'est pas vide mais la case en dessous l'est
            // alors on permute les deux cases
            if (!isEmptyBox(grid, i, j) && isEmptyBox(grid, i, j + 1)) {
                grid->data[nextIndex] = grid->data[index];
                gridEmptyBox(grid, i, j);
            }
        }
    }
}

bool isEmptyBox(const Grid *grid, const unsigned int row, const unsigned int column) {
    return grid->data[row * grid->columns + column] == ' ';
}

bool neighbourIsSameTop(const Grid *grid, const unsigned int row, const unsigned int column) {
    const unsigned int legalIndex = (column - 1) * grid->columns + row;

    // vérifier que l'on accède pas à une valeur hors de la grille
    if (legalIndex >= grid->rows) {
        return false;
    }
    return grid->data[column * grid->columns + row] == grid->data[legalIndex];
}

bool neighbourIsSameBottom(const Grid *grid, const unsigned int row, const unsigned int column) {
    const unsigned int legalIndex = (column + 1) * grid->columns + row;

    // vérifier que l'on accède pas à une valeur hors de la grille
    if (legalIndex >= grid->rows) {
        return false;
    }
    return grid->data[column * grid->columns + row] == grid->data[legalIndex];
}

bool neighbourIsSameLeft(const Grid *grid, const unsigned int row, const unsigned int column) {
    const unsigned int legalIndex = column * grid->columns + (row - 1);

    // vérifier que l'on accède pas à une valeur hors de la grille
    if (legalIndex >= grid->rows) {
        return false;
    }
    return grid->data[column * grid->columns + row] == grid->data[legalIndex];
}

bool neighbourIsSameRight(const Grid *grid, const unsigned int row, const unsigned int column) {
    const unsigned int legalIndex = column * grid->columns + (row + 1);

    // vérifier que l'on accède pas à une valeur hors de la grille
    if (legalIndex >= grid->rows) {
        return false;
    }
    return grid->data[column * grid->columns + row] == grid->data[legalIndex];
}
