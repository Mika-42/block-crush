//
// Created by Matis on 16/12/2024.
//

#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool visitedInit = false;
static size_t visitedLength = 1;

void resetVisited() {
	visitedInit = false;
	visitedLength = 1;
}

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
		printf("%s\n", grid->data[i]);
	}
}

ErrorCode gridEmptyBox(Grid *grid, const Coordinate coord) {
	if (coord.row >= grid->rows || coord.col >= grid->columns) {
		return GRID_SIZE_ERROR;
	}
	grid->data[coord.row][coord.col] = ' ';
	return SUCCESS;
}

void gridFallElement(Grid *grid) {
	// on itère jusqu'à la (n-1) ligne du tableau pour gérer le pire cas possible
	// qui est un élément tout en haut et toute la colonne en dessous est vide
	for (size_t _ = 0; _ < grid->rows - 1; ++_) {
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

	//resetVisited();

	return SUCCESS;
}

bool gridIsValidCoordinate(const Grid *grid, const Coordinate coord) {
	return coord.row < grid->rows && coord.col < grid->columns && coord.row >= 0 && coord.col >= 0;
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

// void findSequence(const Grid *grid, const Coordinate startCoord, Sequence *sequence) {
// 	// déclaré static pour qu'il conserve sa valeur durant les appels récursifs
// 	static size_t seqLen = 0;
//
// 	const Coordinate coordRight = {startCoord.row, startCoord.col + 1};
// 	const Coordinate coordLeft = {startCoord.row, startCoord.col - 1};
// 	const Coordinate coordBottom = {startCoord.row + 1, startCoord.col};
// 	const Coordinate coordTop = {startCoord.row - 1, startCoord.col};
//
// 	const bool isNeighbourRight = isSameSymbol(grid, startCoord, coordRight);
// 	const bool isNeighbourLeft = isSameSymbol(grid, startCoord, coordLeft);
// 	const bool isNeighbourBottom = isSameSymbol(grid, startCoord, coordBottom);
// 	const bool isNeighbourTop = isSameSymbol(grid, startCoord, coordTop);
// 	/**
// 	 * On initialise le tableau des coordonnées visitées avec les valeurs maximales des entiers long non signés
// 	 * afin d'éviter d'avoir des coordonnées aléatoires déjà présentes en mémoire dans le tableau.
// 	 *
// 	 * - 'visitedInit', 'visitedLength', 'visited[]' sont déclarés 'static' pour qu'ils ne soient pas initialisé à chaque appel
// 	 * de la fonction mais uniquement au premier.
// 	 * Après quoi on met 'visitedInit' à true pour que les instructions qui suivent ne s'exécutent qu'une seule fois
// 	 */
//
// 	static Coordinate visited[longestSequencePossible] = {};
//
// 	if (!visitedInit) {
// 		visitedInit = true;
// 		for (size_t i = 0; i < longestSequencePossible; ++i) {
// 			visited[i] = (Coordinate){INT_MAX, INT_MAX};
// 		}
// 	}
//
// 	/**
// 	 * A L G O R I T H M E
// 	 *
// 	 * 1. coordonées non visité ?
// 	 *		Oui -> ajouter à la séquence
// 	 *
// 	 * 2. un voisin à droite qui n'as pas été visité ?
// 	 *		Oui -> ajouter à la séquence retourner à l'étape 1 avec les coordonées du voisin de droite
// 	 *
// 	 * 3. un voisin à gauche qui n'as pas été visité ?
// 	 *		Oui -> ajouter à la séquence retourner à l'étape 1 avec les coordonées du voisin de gauche
// 	 *
// 	 * 4. un voisin en bas qui n'as pas été visité ?
// 	 *		Oui -> ajouter à la séquence retourner à l'étape 1 avec les coordonées du voisin du bas
// 	 */
// 	if (!isSubDataOf(visited, longestSequencePossible, startCoord)) {
// 		visited[visitedLength++ - 1] = sequence->data[++seqLen - 1] = startCoord;
// 	}
//
// 	if (isNeighbourRight && !isSubDataOf(visited, longestSequencePossible, coordRight)) {
// 		visited[visitedLength++ - 1] = sequence->data[seqLen++] = coordRight;
// 		return findSequence(grid, coordRight, sequence);
// 	}
//
// 	if (isNeighbourLeft && !isSubDataOf(visited, longestSequencePossible, coordLeft)) {
// 		visited[visitedLength++ - 1] = sequence->data[seqLen++] = coordLeft;
// 		return findSequence(grid, coordLeft, sequence);
// 	}
//
// 	if (isNeighbourBottom && !isSubDataOf(visited, longestSequencePossible, coordBottom)) {
// 		visited[visitedLength++ - 1] = sequence->data[seqLen++] = coordBottom;
// 		return findSequence(grid, coordBottom, sequence);
// 	}
//
// 	if (isNeighbourTop && !isSubDataOf(visited, longestSequencePossible, coordTop)) {
// 		visited[visitedLength++ - 1] = sequence->data[seqLen++] = coordTop;
// 		return findSequence(grid, coordTop, sequence);
// 	}
//
// 	if (visitedLength >= longestSequencePossible) {
// 		visitedLength = longestSequencePossible - 1;
// 	}
//
// 	sequence->length = seqLen >= longestSequencePossible ? longestSequencePossible - 1 : seqLen;
//
// 	seqLen = 0;
// }
//
// void getAllSequences(const Grid *grid, const char letter, SequenceArray *sequences) {
// 	sequences->length = 0;
//
// 	for (size_t i = 0; i < grid->rows; i++) {
// 		for (size_t j = 0; j < grid->columns; j++) {
// 			const Coordinate coordinate = {i, j};
//
// 			if (grid->data[coordinate.row][coordinate.col] != letter) {
// 				continue;
// 			}
//
// 			findSequence(grid, coordinate, &sequences->data[sequences->length]);
//
// 			if (sequences->data[sequences->length].length < 1) {
// 				continue;
// 			}
//
// 			sequences->length++;
// 		}
// 	}
// 	resetVisited();
// }

bool coordEquals(const Coordinate coord1, const Coordinate coord2) {
	return coord1.col == coord2.col && coord1.row == coord2.row;
}

// void getLongest(const SequenceArray *sequences, size_t *length, size_t *index) {
// 	size_t len = 0;
//
// 	for (int i = 0; i < sequences->length; i++) {
// 		if (sequences->data[i].length > len) {
// 			len = sequences->data[i].length;
// 			*index = i;
// 		}
// 	}
// 	*length = len;
// }

Sequence getLongestSequences(const Grid *grid);

size_t removeLongestSequences(Grid *grid) {

	const Sequence sequence = getLongestSequences(grid);

	if (sequence.empty) { return 0; }

	for (int i = 0; i < sequence.length; ++i) {
		gridEmptyBox(grid, sequence.data[i]);
	}

	return sequence.length;
}

Sequence getLongestSequences(const Grid *grid) {

	constexpr Coordinate directions[4] = {
		(Coordinate){-1, 0}, // Haut
		(Coordinate){1, 0},  // Bas
		(Coordinate){0, -1}, // Gauche
		(Coordinate){0, 1}   // Droite
	};

	int visited[maxSequencePossible][longestSequencePossible] = {};

	Sequence sequence = {};
	sequence.length = 0;

	for (int i = 0; i < grid->rows; i++) {
		for (int j = 0; j < grid->columns; j++) {
			if (visited[i][j] || grid->data[i][j] == ' ') continue;

			// Commencer une nouvelle séquence
			Sequence seq = {};
			seq.length = 0;

			// Utiliser une pile pour le DFS
			Coordinate stack[longestSequencePossible];
			int stack_size = 0;

			stack[stack_size++] = (Coordinate){i, j};

			while (stack_size > 0) {
				const Coordinate current = stack[--stack_size];
				if (visited[current.row][current.col]) continue;

				visited[current.row][current.col] = 1;
				seq.data[seq.length++] = current;

				// Vérifier les voisins
				for (int d = 0; d < 4; d++) {
					const int x = current.row + directions[d].row;
					const int y = current.col + directions[d].col;
					const bool validCoordinate = gridIsValidCoordinate(grid, (Coordinate){x, y});
					const bool sameLetter = grid->data[x][y] == grid->data[i][j];

					if (validCoordinate && !visited[x][y] && sameLetter) {
						stack[stack_size++] = (Coordinate){x, y};
					}
				}
			}

			// Vérifier si la séquence trouvée est la plus longue
			if ((sequence.empty = seq.length >= 4 && seq.length > sequence.length)) {
				sequence = seq;
			}
		}
	}

	return sequence;
}