//
// Created by Matis on 16/12/2024.
//

#ifndef GRID_H
#define GRID_H

#include <time.h>
#include "error.h"
#include <stdlib.h>

typedef unsigned int ui32;

/**
 * Structure content les données relatives à la grille
 * - columns : nombre de colonnes
 * - rows : nombre de lignes
 * - data : données de la grille
 */
typedef struct {
    ui32 columns;
    ui32 rows;
    char *data;
} Grid;

/**
 * @brief alloue dynamiquement un tableau de taille colonnes * lignes
 * @param grid pointeur sur la structure Grid à allouer
 * @return ErrorCode
 *  TETRIS_GRID_SIZE_ERROR                - taille de grille négative ou nulle
 *  TETRIS_DYNAMIC_ALLOCATION_FAILED      - allocation dynamique a échouée
 *  TETRIS_SUCCESS                        - tout est correct
 */
ErrorCode gridAlloc(Grid *grid);

/**
 * @brief désalloue la mémoire précédemment allouée
 * @param grid pointeur sur la structure Grid à désallouer
 * @return ErrorCode
 *  TETRIS_FREE_DYNAMIC_ALLOCATION_FAILED - la libération de l'espace allouée a échoué
 *  TETRIS_SUCCESS                        - tout est correct
 */
ErrorCode gridFree(Grid *grid);

/**
 * @brief remplire une grille avec les lettres A, O, X, H de manière aléatoire
 * @param grid structure à remplire
 */
void gridFill(const Grid *grid);

/**
 * @brief affiche une grille dans la console
 * @param grid structure à afficher
 */
void gridPrint(const Grid *grid);

/**
 * @brief efface une lettre à une certaine position dans le tableau
 * @param grid
 * @param rows
 * @param columns
 * @return ErrorCode
 *  TETRIS_DYNAMIC_ALLOCATION_FAILED      - le pointeur grid ou grid->data est nul
 *  TETRIS_GRID_SIZE_ERROR                - tentative d'accès à des données hors du tableau
 *  TETRIS_SUCCESS                        - tout est correct
 */
ErrorCode gridEmptyBox(const Grid *grid, ui32 rows, ui32 columns);

/**
 * @brief fait tomber les élément vers le bas de la grille s'il y a un vide en dessous d'eux
 * @param grid
 */
void gridFallElement(const Grid *grid);

/**
 * @brief vérifie si la case [row][column] est vide
 * @param grid
 * @param row
 * @param column
 * @return bool
 */
bool isEmptyBox(const Grid *grid, ui32 row, ui32 column);

/**
 * @brief échange de place deux élément de coordonées [row1][column1] et [row2][column2]
 * @param grid
 * @param row1
 * @param column1
 * @param row2
 * @param column2
 * @return bool
 *  TETRIS_DYNAMIC_ALLOCATION_FAILED      - le pointeur grid ou grid->data est nul
 *  TETRIS_GRID_SIZE_ERROR                - tentative d'accès à des données hors du tableau
 *  TETRIS_SUCCESS                        - tout est correct
 */
ErrorCode swapBoxes(const Grid *grid, ui32 row1, ui32 column1, ui32 row2, ui32 column2);

//---
// bool neighbourIsSameTop(const Grid *grid, ui32 row, ui32 column);
//
// bool neighbourIsSameBottom(const Grid *grid, ui32 row, ui32 column);
//
// bool neighbourIsSameLeft(const Grid *grid, ui32 row, ui32 column);
//
// bool neighbourIsSameRight(const Grid *grid, ui32 row, ui32 column);

#endif //GRID_H
