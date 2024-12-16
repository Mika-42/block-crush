//
// Created by Matis on 16/12/2024.
//

#ifndef GRID_H
#define GRID_H

#include "error.h"

/**
 * Structure content les données relatives à la grille
 * - columns : nombre de colonnes
 * - rows : nombre de lignes
 * - data : données de la grille
 */

typedef struct
{
    unsigned int columns;
    unsigned int rows;
    char* data;
} Grid;

ErrorCode gridAlloc(Grid* grid);
ErrorCode gridFree(Grid* grid);
void gridFill(Grid* grid);
void gridPrint(Grid* grid);

#endif //GRID_H
