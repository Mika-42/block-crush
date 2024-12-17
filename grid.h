//
// Created by Matis on 16/12/2024.
//

#ifndef GRID_H
#define GRID_H

#include <time.h>
#include "error.h"
#include <stdlib.h>

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

/**
 * @brief alloue dynamiquement un tableau de taille colonnes * lignes
 * @param grid pointeur sur la structure Grid à allouer
 * @return ErrorCode
 *  TETRIS_GRID_SIZE_ERROR                - taille de grille négative ou nulle
 *  TETRIS_DYNAMIC_ALLOCATION_FAILED      - allocation dynamique a échouée
 *  TETRIS_SUCCESS                        - tout est correct
 */
ErrorCode gridAlloc(Grid* grid);

/**
 * @brief désalloue la mémoire précédemment allouée
 * @param grid pointeur sur la structure Grid à désallouer
 * @return ErrorCode
 *  TETRIS_FREE_DYNAMIC_ALLOCATION_FAILED - la libération de l'espace allouée a échoué
 *  TETRIS_SUCCESS                        - tout est correct
 */
ErrorCode gridFree(Grid* grid);

/**
 * @brief remplire une grille avec les lettres A, O, X, H de manière aléatoire
 * @param grid structure à remplire
 */
void gridFill(const Grid* grid);

/**
 * @brief affiche une grille dans la console
 * @param grid structure à afficher
 */
void gridPrint(const Grid* grid);

/**
 * @brief efface une lettre à une certaine position dans le tableau
 * @param grid
 * @param rows
 * @param columns
 */
ErrorCode gridEmptyBox(const Grid* grid, unsigned int rows, unsigned int columns);

/**
 * @brief fait tomber les élément vers le bas de la grille s'il y a un vide en dessous d'eux
 * @param grid
 */
void gridFallElement(const Grid* grid);

bool isEmptyBox(const Grid* grid, unsigned int row, unsigned int column);

void swapBoxes(Grid* grid, unsigned int row1, unsigned int column1, unsigned int row2, unsigned int column2);
//---
bool neighbourIsSameTop(const Grid* grid, unsigned int row, unsigned int column);
bool neighbourIsSameBottom(const Grid* grid, unsigned int row, unsigned int column);
bool neighbourIsSameLeft(const Grid* grid, unsigned int row, unsigned int column);
bool neighbourIsSameRight(const Grid* grid, unsigned int row, unsigned int column);

#endif //GRID_H
