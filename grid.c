//
// Created by Matis on 16/12/2024.
//

#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gridFill(Grid *grid) {
	for (size_t i = 0; i < grid->rows; ++i) {
		for (size_t j = 0; j < grid->columns; ++j) {
			constexpr char letter[4] = "HOAX";
			grid->data[i][j] = letter[rand() % 4];
		}
	}
}

void gridPrint(const Grid *grid) {
	for (size_t i = 0; i < grid->rows; ++i) {
		printf("\n");
		for (size_t j = 0; j < grid->columns; ++j) {
			printf("%c", grid->data[i][j]);
		}
	}
	printf("\n");
}

ErrorCode gridEmptyBox(Grid *grid, const Coordinate coord) {
	if (coord.row >= grid->rows || coord.col >= grid->columns) {
		return GRID_SIZE_ERROR;
	}

	grid->data[coord.row][coord.col] = ' ';
	return SUCCESS;
}

void gridFallElement(Grid *grid) {
	// on s'arrête une ligne avant pour ne pas chercher
	// le voisin du dessous de la dernière ligne
	for (size_t i = 0; i < grid->rows - 1; ++i) {
		for (size_t j = 0; j < grid->columns; ++j) {
			// si la case actuelle n'est pas vide, mais la case en dessous l'est alors, on permute les deux cases
			const Coordinate coordCurrent = {i, j};
			const Coordinate coordUnder = {i + 1, j};

			if (!isEmptyBox(grid, coordCurrent) && isEmptyBox(grid, coordUnder)) {
				swapBoxes(grid, coordCurrent, coordUnder);
			}
		}
	}
}

bool isEmptyBox(const Grid *grid, const Coordinate coord) {
	return grid->data[coord.row][coord.col] == ' ';
}

ErrorCode swapBoxes(Grid *grid, const Coordinate coord1, const Coordinate coord2) {
	if (coord1.row >= grid->rows || coord1.col >= grid->columns) {
		return GRID_SIZE_ERROR;
	}
	if (coord2.row >= grid->rows || coord2.col >= grid->columns) {
		return GRID_SIZE_ERROR;
	}

	const char temp = grid->data[coord1.row][coord1.col];
	grid->data[coord1.row][coord1.col] = grid->data[coord2.row][coord2.col];
	grid->data[coord2.row][coord2.col] = temp;

	return SUCCESS;
}

bool gridIsValidCoordinate(const Grid *grid, const Coordinate coord) {
	return coord.row < grid->rows && coord.col < grid->columns;
}

bool isSubDataOf(const Coordinate *array, const size_t size, const Coordinate coord) {
	for (size_t i = 0; i < size; ++i) {
		if (coordEquals(array[i], coord)) {
			return true;
		}
	}
	return false;
}

bool isSameSymbol(const Grid *grid, const Coordinate coord1, const Coordinate coord2) {
	if (!gridIsValidCoordinate(grid, coord1)) {
		return false;
	}

	if (!gridIsValidCoordinate(grid, coord2)) {
		return false;
	}

	return grid->data[coord1.row][coord1.col] == grid->data[coord2.row][coord2.col];
}

void findSequence(const Grid *grid, const Coordinate startCoord, Sequence *sequence) {
	// déclaré static pour qu'il conserve sa valeur durant les appels récursifs
	static size_t seqLen = 0;

	const Coordinate coordRight = {startCoord.row, startCoord.col + 1};
	const Coordinate coordLeft = {startCoord.row, startCoord.col - 1};
	const Coordinate coordBottom = {startCoord.row + 1, startCoord.col};

	const bool isNeighbourRight = isSameSymbol(grid, startCoord, coordRight);
	const bool isNeighbourLeft = isSameSymbol(grid, startCoord, coordLeft);
	const bool isNeighbourBottom = isSameSymbol(grid, startCoord, coordBottom);

	/**
	 * On initialise le tableau des coordonnées visitées avec les valeurs maximales des entiers long non signés
	 * afin d'éviter d'avoir des coordonnées aléatoires déjà présentes en mémoire dans le tableau.
	 *
	 * - 'visitedInit', 'visitedLength', 'visited[]' sont déclarés 'static' pour qu'ils ne soient pas initialisé à chaque appel
	 * de la fonction mais uniquement au premier.
	 * Après quoi on met 'visitedInit' à true pour que les instructions qui suivent ne s'exécutent qu'une seule fois
	 */
	static bool visitedInit = false;
	static size_t visitedLength = 1;
	static Coordinate visited[longestSequencePossible] = {};

	if (!visitedInit) {
		visitedInit = true;
		for (size_t i = 0; i < longestSequencePossible; ++i) {
			visited[i] = (Coordinate){ULLONG_MAX, ULLONG_MAX};
		}
	}

	/**
	 * A L G O R I T H M E
	 *
	 * 1. coordonées non visité ?
	 *		Oui -> ajouter à la séquence
	 *
	 * 2. un voisin à droite qui n'as pas été visité ?
	 *		Oui -> ajouter à la séquence retourner à l'étape 1 avec les coordonées du voisin de droite
	 *
	 * 3. un voisin à gauche qui n'as pas été visité ?
	 *		Oui -> ajouter à la séquence retourner à l'étape 1 avec les coordonées du voisin de gauche
	 *
	 * 4. un voisin en bas qui n'as pas été visité ?
	 *		Oui -> ajouter à la séquence retourner à l'étape 1 avec les coordonées du voisin du bas
	 */
	if (!isSubDataOf(visited, longestSequencePossible, startCoord)) {
		visited[visitedLength++ - 1] = sequence->data[++seqLen - 1] = startCoord;
	}

	if (isNeighbourRight && !isSubDataOf(visited, longestSequencePossible, coordRight)) {
		visited[visitedLength++ - 1] = sequence->data[seqLen++] = coordRight;
		return findSequence(grid, coordRight, sequence);
	}

	if (isNeighbourLeft && !isSubDataOf(visited, longestSequencePossible, coordLeft)) {
		visited[visitedLength++ - 1] = sequence->data[seqLen++] = coordLeft;
		return findSequence(grid, coordLeft, sequence);
	}

	if (isNeighbourBottom && !isSubDataOf(visited, longestSequencePossible, coordBottom)) {
		visited[visitedLength++ - 1] = sequence->data[seqLen++] = coordBottom;
		return findSequence(grid, coordBottom, sequence);
	}

	if (visitedLength >= longestSequencePossible) {
		visitedLength = longestSequencePossible - 1;
	}

	sequence->length = seqLen >= longestSequencePossible ? longestSequencePossible - 1 : seqLen;
	seqLen = 0;
}

void getAllSequences(const Grid *grid, const char letter, SequenceArray *sequences) {
	sequences->length = 0;

	for (size_t i = 0; i < grid->rows; i++) {
		for (size_t j = 0; j < grid->columns; j++) {
			const Coordinate coordinate = {i, j};

			if (grid->data[coordinate.row][coordinate.col] != letter) {
				continue;
			}

			findSequence(grid, coordinate, &sequences->data[sequences->length]);

			if (sequences->data[sequences->length].length < 1) {
				continue;
			}

			sequences->length++;
		}
	}
}

bool coordEquals(const Coordinate coord1, const Coordinate coord2) {
	return coord1.col == coord2.col && coord1.row == coord2.row;
}

void getLongest(const SequenceArray *sequences, size_t *length, size_t *index) {
	*length = 0;

	for (int i = 0; i < sequences->length; i++) {
		if (sequences->data[i].length <= *length) {
			continue;
		}
		*length = sequences->data[i].length;
		*index = i;
	}
}

size_t removeLongestSequences(Grid *grid) {
	SequenceArray sequences[4] = {};

	getAllSequences(grid, 'H', &sequences[0]);
	getAllSequences(grid, 'O', &sequences[1]);
	getAllSequences(grid, 'A', &sequences[2]);
	getAllSequences(grid, 'X', &sequences[3]);

	size_t maxLongestSequenceLength = 0;
	Sequence *longestSequencePtr = nullptr;

	size_t longestSequencesLength[4] = {};
	size_t longestSequencesIndex[4] = {};

	getLongest(&sequences[0], &longestSequencesLength[0], &longestSequencesIndex[0]);
	getLongest(&sequences[1], &longestSequencesLength[1], &longestSequencesIndex[1]);
	getLongest(&sequences[2], &longestSequencesLength[2], &longestSequencesIndex[2]);
	getLongest(&sequences[3], &longestSequencesLength[3], &longestSequencesIndex[3]);

	// Récupérer l'indice de la séquence la plus longue
	for (int i = 0; i < 4; i++) {
		if (longestSequencesLength[i] > maxLongestSequenceLength) {
			maxLongestSequenceLength = longestSequencesLength[i];
			longestSequencePtr = &sequences[i].data[longestSequencesIndex[i]];
		}
	}

	if (maxLongestSequenceLength < 4) {
		return 0;
	}

	for (size_t i = 0; i < longestSequencePtr->length; i++) {
		gridEmptyBox(grid, longestSequencePtr->data[i]);
	}

	return maxLongestSequenceLength;
}
