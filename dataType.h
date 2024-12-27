//
// Created by Matis on 16/12/2024.
//

#ifndef DATATYPE_H
#define DATATYPE_H

#include <stddef.h>

/**
 * La plus grande grille possible est du 12x6 donc 72 éléments
 * Supposons que la grille soit remplie du meme élément alors
 * la plus grande séquence possible est 72
 * ----------------------------------------------------------
 * XXXXXXXXXXXX
 * XXXXXXXXXXXX
 * XXXXXXXXXXXX
 * XXXXXXXXXXXX
 * XXXXXXXXXXXX
 * XXXXXXXXXXXX
 * XXXXXXXXXXXX
 */
constexpr size_t longestSequencePossible = 72;

/**
 * La plus grande grille possible est du 12x6 donc 72 éléments
 * Supposons que la grille soit remplie de manière alterné
 * le maximum de séquences possible est 72 / 2 = 36
 * ----------------------------------------------------------
 * XOXOXOXOXOXO
 * OXOXOXOXOXOX
 * XOXOXOXOXOXO
 * OXOXOXOXOXOX
 * XOXOXOXOXOXO
 * OXOXOXOXOXOX
 */
constexpr size_t maxSequencePossible = 36;

typedef struct {
	int row;
	int col;
} Coordinate;

typedef struct {
	Coordinate data[longestSequencePossible];
	size_t length;
	bool empty;
} Sequence;

typedef struct {
	Sequence data[maxSequencePossible];
	size_t length;
} SequenceArray;

typedef enum : size_t {
	SUCCESS = 0,
	GENERIC_ERROR,
	GRID_SIZE_ERROR,
} ErrorCode;

#endif //DATATYPE_H
