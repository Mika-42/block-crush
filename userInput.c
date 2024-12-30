//
// Created by Matis on 29/12/2024.
//

/*
 * Cet en-tête est nécessaire à l'utilisation des prédicats
 * 'islower', 'isupper', 'isdigit'
 */
#include <ctype.h>
/**
 * Cet en-tête est nécessaire à l'utilisation des entrées/sorties
 * 'printf', 'scanf'
 */
#include <stdio.h>

#include "userInput.h"
#include "grid.h"

ErrorCode strToCoord(const char in_coord[2], Coordinate *coordinate) {

	const bool isAlphaNum = isupper(in_coord[0]) && isdigit(in_coord[1]);
	const bool isNumAlpha = isupper(in_coord[1]) && isdigit(in_coord[0]);
	const bool is_alphaNum = islower(in_coord[0]) && isdigit(in_coord[1]);
	const bool isNum_alpha = islower(in_coord[1]) && isdigit(in_coord[0]);

	if (isAlphaNum) {
		coordinate->row = in_coord[1] - '0' - 1;
		coordinate->col = in_coord[0] - 'A';
		return SUCCESS;
	}

	if (isNumAlpha) {
		coordinate->row = in_coord[0] - '0' - 1;
		coordinate->col = in_coord[1] - 'A';
		return SUCCESS;
	}

	if (is_alphaNum) {
		coordinate->row = in_coord[1] - '0' - 1;
		coordinate->col = in_coord[0] - 'a';
		return SUCCESS;
	}

	if (isNum_alpha) {
		coordinate->row = in_coord[0] - '0' - 1;
		coordinate->col = in_coord[1] - 'a';
		return SUCCESS;
	}

	return GENERIC_ERROR;
}

Coordinate getInputCoord(const char* msg) {
	//todo improve

	// variable temporaire pour récupérer la saisie
	// 3 = 2 char + '\0'

	char coordInput[3];

	Coordinate coord= {};

	do {
		printf("%s", msg);
		scanf("%2s", coordInput);

		/**
		 * On vide le tampon d'entrée pour ne pas
		 * récupérer des caractères supplémentaires
		 */
		fflush(stdin);

	}
	while (strToCoord(coordInput, &coord) != SUCCESS);

	return coord;
}

void secureGetCase1(const Grid *grid, Coordinate *coord) {
	bool looping = true;
	while (looping)
	{
		*coord = getInputCoord("Case 1: ");

		if (!gridIsValidCoordinate(grid, *coord)) {
			printf("Coordonnées invalides.\n");
			continue;
		}
		if (gridIsEmptyBox(grid, *coord)) {
			printf("Choisissez une case non-vide.\n");
			continue;
		}

		looping = false;
	}
}

bool secureGetCase2(Grid grid, const Coordinate coord1, Coordinate *coord2) {
	bool looping = true;
	while (looping)
	{

		*coord2 = getInputCoord("Case 2: ");

		if (!gridIsValidCoordinate(&grid, *coord2)) {
			printf("Coordonnées invalides.\n");
			continue;
		}

		if (gridIsEmptyBox(&grid, *coord2)) {
			printf("Choisissez une case non-vide.\n");
			continue;
		}

		if (!isNeighbour(coord1, *coord2)) {
			printf("Choisissez une case adjacente a la premiere.\n");
			continue;
		}

		// On vérifie si la permutation aboutie à une séquence valide
		gridSwapBoxes(&grid, coord1, *coord2);
		const Sequence sequence = getLongestSequences(&grid);

		if (sequence.length == 0) {
			printf("Permutation non valide.\n");

			return false;
		}

		looping = false;

	}
	return true;
}