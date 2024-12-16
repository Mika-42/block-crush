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
void gridPrint(Grid* grid);

#endif //GRID_H
