//
// Created by Matis on 16/12/2024.
//

/**
 * Cet en-tête est nécessaire pour manipuler le terminal windows
 * NB : l'utilisation de ce fichier retire la portabilité du code
 *		et le rend fonctionnel uniquement sous le système d'exploitation Windows
 */
#include <windows.h>

/**
 * Cet entête est nécessaire à la génération de nombre aléatoire
 */
#include <stdlib.h>

/**
 * Cet entête est nécessaire à l'utilisation des flux d'entrée/sortie
 * tel que 'printf', 'scanf'
 */
#include <stdio.h>

#include "grid.h"

//===Prédicats=====================================================================//
bool gridIsEmptyBox(const Grid *grid, const Coordinate coord) {
	return grid->data[coord.row][coord.col] == ' ';
}

bool gridIsValidCoordinate(const Grid *grid, const Coordinate coord) {
	return coord.row < grid->rows && coord.col < grid->columns;
}

bool coordEquals(const Coordinate coord1, const Coordinate coord2) {
	return coord1.col == coord2.col && coord1.row == coord2.row;
}
//==================================================================================//

void gridFill(Grid *grid) {

	/**
	 * Fonctionnement de l'algorithme:
	 *	La grille d'entrée est suposée vide
	 *
	 * 1.	On remplit aléatoirement les espaces vide
	 *		de la grilles avec les lettres H, O, A, X
	 *
	 * 2.	Si une séquence de plus de 4 élément est présente
	 *			Alors on la suprime puis on retourne à l'étape 1
	 *		Sinon on quitte la fonction
	 */

	do {

		for (size_t i = 0; i < grid->rows; ++i) {
			for (size_t j = 0; j < grid->columns; ++j) {

				constexpr char letter[4] = "HOAX";

				if (gridIsEmptyBox(grid, (Coordinate){i, j})) {
					grid->data[i][j] = letter[rand() % 4];
				}

			}
		}
	}while (removeLongestSequences(grid));
}

void gridPrint(const Grid *grid) {

	//Attendre 700ms
	Sleep(700);

	//Effacer la console
	system("cls");

	printf("    ");
	for (char j = 'A'; j < grid->columns + 'A'; ++j) {
		printf("%c ", j);
	}


	printf("\n   ┏");
	for (size_t j = 1; j < grid->columns; ++j) {
		printf("─┬");
	}
	printf("─┓\n");

	for (size_t i = 0; i < grid->rows; ++i) {

		i < 9 ? printf(" %llu", i+1) : printf("%llu", i+1);

		printf(" ");

		for (size_t j = 0; j < grid->columns; ++j) {

			printf("│%c", grid->data[i][j]);
		}
		printf("│\n");

		if (i != grid->rows - 1) {
			printf("   ├");

			for(size_t j = 1; j < grid->columns; ++j) {
				printf("─┼");
			}
			printf("─┤\n");
		}
	}

	printf("   ┗─");
	for (size_t j = 1; j < grid->columns; ++j) {
		printf("┴─");
	}
	printf("┛\n\n");
}

ErrorCode gridEmptyBox(Grid *grid, const Coordinate coord) {
	if (!gridIsValidCoordinate(grid, coord)) return GRID_SIZE_ERROR;
	grid->data[coord.row][coord.col] = ' ';
	return SUCCESS;
}

ErrorCode gridSwapBoxes(Grid *grid, const Coordinate coord1, const Coordinate coord2) {

	if (!gridIsValidCoordinate(grid, coord1) || !gridIsValidCoordinate(grid, coord2)) {
		return GRID_SIZE_ERROR;
	}

	/**
	 * Cette méthode d'échange de deux variables avec XOR fonctionne
	 * car 'char' est un type numérique 8-bits signé. avec des type de données
	 * plus complexe (structures, chaines de caractère, etc...) il faudra
	 * utiliser une variable temporaire
	 *
	 * Exemple:
	 *		On prend a = 5 (0101) et b = 3 (0011)
	 *
	 *		Étape 1 : a = a XOR b
	 *		a = 0101
	 *		b = 0011
	 *		-----------
	 *		a = 0110
	 *
	 *		Étape 2 : b = a XOR b
	 *		a = 0110
	 *		b = 0011
	 *		-----------
	 *      b = 0101  (5 en décimal, qui est l'ancienne valeur de a)
	 *
	 *		Étape 3 : a = a XOR b
	 *		a = 0110
	 *		b = 0101
	 *		-----------
	 *		a = 0011  (3 en décimal, qui est l'ancienne valeur de b)
	 */
	grid->data[coord1.row][coord1.col] ^= grid->data[coord2.row][coord2.col];
	grid->data[coord2.row][coord2.col] ^= grid->data[coord1.row][coord1.col];
	grid->data[coord1.row][coord1.col] ^= grid->data[coord2.row][coord2.col];

	return SUCCESS;
}

void gridFallElement(Grid *grid) {
	/**
	 * on itère jusqu'à la (n-1) ligne du tableau
	 *		ce qui représente le pire cas possible:
	 *
	 *		 - un élément en haut et toute la colonne en dessous est vide
	 *
	 */
	for (size_t _ = 1; _ < grid->rows; ++_) {

		for (size_t i = 0; i < grid->rows - 1; ++i) {
			for (size_t j = 0; j < grid->columns; ++j) {

				const Coordinate coordCurrent = {i, j};
				const Coordinate coordUnder = {i + 1, j};

				if (!gridIsEmptyBox(grid, coordCurrent) && gridIsEmptyBox(grid, coordUnder)) {
					gridSwapBoxes(grid, coordCurrent, coordUnder);
				}
			}
		}
	}
}

size_t removeLongestSequences(Grid *grid) {

	const Sequence sequence = getLongestSequences(grid);

	if (sequence.empty) { return 0; }

	for (int i = 0; i < sequence.length; ++i) {
		/**
		 * Ici on ne vérifira pas les codes d'erreur
		 * car pour figurer dans une séquence les coordonées
		 * sont obligatoirement dans la grille
		 */
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

	int visited[maxRow][maxCol] = {};

	Sequence sequence = {.length = 0};

	for (int i = 0; i < grid->rows; i++) {
		for (int j = 0; j < grid->columns; j++) {

			// Vérifier si la case a déjà été visité ou si elle est vide
			if (visited[i][j] || grid->data[i][j] == ' ') continue;

			// Créer une nouvelle séquence temporaire
			Sequence seq = {.length = 0};

			// Utiliser une pile pour le DFS (Depth-first search)
			Coordinate stack[longestSequencePossible];
			int stack_size = 0;

			// Empiler (i, j)
			stack[stack_size++] = (Coordinate){i, j};

			while (stack_size > 0) {
				const Coordinate current = stack[--stack_size];
				if (visited[current.row][current.col]) continue;

				// Marquer les coordonnées actuelles comme visité
				visited[current.row][current.col] = 1;

				// Ajouter les coordonnées actuelles à la séquence temporaire
				seq.data[seq.length++] = current;

				// Vérifier les voisins
				for (int d = 0; d < 4; d++) {

					const size_t x = current.row + directions[d].row;
					const size_t y = current.col + directions[d].col;

					const bool validCoordinate = gridIsValidCoordinate(grid, (Coordinate){x, y});
					const bool sameLetter = grid->data[x][y] == grid->data[i][j];

					if (validCoordinate && !visited[x][y] && sameLetter) {

						// Empiler (x, y)
						stack[stack_size++] = (Coordinate){x, y};
					}
				}
			}

			// Vérifier si la séquence trouvée est la plus longue
			if ((sequence.empty = (seq.length >= 4 && seq.length > sequence.length))) {
				sequence = seq;
			}
		}
	}

	return sequence;
}