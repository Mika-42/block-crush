//
// Created by Matis on 16/12/2024.
//

#ifndef GRID_H
#define GRID_H

#include "dataType.h"

typedef struct {
	size_t columns;
	size_t rows;
	char data[maxSequencePossible][longestSequencePossible];
} Grid;

/**
 * @brief Remplir une grille avec les lettres A, O, X, H de manière aléatoire
 * @param grid Structure à remplire
 */
void gridFill(Grid *grid);

/**
 * @brief Affiche une grille dans la console
 * @param grid structure à afficher
 */
void gridPrint(const Grid *grid);

/**
 * @brief Efface une lettre à une certaine position dans le tableau
 * @param grid
 * @param coord
 * @return ErrorCode
 *  DYNAMIC_ALLOCATION_FAILED      - le pointeur grid ou grid->data est nul
 *  GRID_SIZE_ERROR                - tentative d'accès à des données hors du tableau
 *  SUCCESS                        - tout est correct
 */
ErrorCode gridEmptyBox(Grid *grid, Coordinate coord);

/**
 * @brief Fait tomber les éléments vers le bas de la grille s'il y a un vide en dessous d'eux
 * @param grid
 */
void gridFallElement(Grid *grid);

/**
 * @brief vérifie si la case [row][column] est vide
 * @param grid
 * @param coord
 * @return bool
 */
bool isEmptyBox(const Grid *grid, Coordinate coord);

/**
 * @brief Échange de place deux éléments de coordonnées [row1][column1] et [row2][column2]
 * @param grid
 * @param coord1
 * @param coord2
 * @return ErrorCode
 *  DYNAMIC_ALLOCATION_FAILED      - le pointeur grid ou grid->data est nul
 *  GRID_SIZE_ERROR                - tentative d'accès à des données hors du tableau
 *  SUCCESS                        - tout est correct
 */
ErrorCode swapBoxes(Grid *grid, Coordinate coord1, Coordinate coord2);

/**
 * @brief Vérifie si les coordonnées n'accèdent pas à des espaces mémoires en dehors de la grille
 * @param grid
 * @param coord
 * @return bool
 */
bool gridIsValidCoordinate(const Grid *grid, Coordinate coord);

/**
 * @brief Vérifie si deux coordonnées sont égales
 * @param coord1
 * @param coord2
 * @return bool
 */
bool coordEquals(const Coordinate coord1, const Coordinate coord2);

size_t removeLongestSequences(Grid *grid);

#endif //GRID_H
