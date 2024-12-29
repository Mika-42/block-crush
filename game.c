//
// Created by Matis on 29/12/2024.
//

#include "game.h"
#include "userInput.h"

/**
 * Cet en-tête est nécessaire pour utiliser 'printf'
 */
#include <stdio.h>

/**
 * Cet en-tête est nécessaire pour utiliser 'memset'
 */
#include <string.h>


bool gameOver(Grid grid) {

	const Coordinate directions[4] =
	{
		(Coordinate){+1,0}, // Bas
		(Coordinate){-1,0}, // Haut
		(Coordinate){0,+1}, // Droite
		(Coordinate){0,-1}, // Gauche
	};

	// Pour chaque direction
	for (size_t k = 0; k < 4; k++) {

		// Parcourir la grille
		for (size_t i = 0; i < grid.rows; i++) {
			for (size_t j = 0; j < grid.columns; j++) {

				//stocker les coordonnées actuelles
				const Coordinate coordinate = {i,j};

				//stocker les coordonnées de la k-ième direction
				const Coordinate neighbour = {i + directions[k].row,j + directions[k].col };

				if (!gridIsValidCoordinate(&grid, neighbour) ||
					gridIsEmptyBox(&grid, neighbour) ||
					gridIsEmptyBox(&grid, coordinate)) {
					continue;
					}

				// Vérifier si la grille contient une séquence viable
				gridSwapBoxes(&grid, neighbour, coordinate);
				const Sequence sequence = getLongestSequences(&grid);
				gridSwapBoxes(&grid, neighbour, coordinate);

				if (sequence.length != 0) {
					return false;
				}
			}
		}
	}
	return true;
}

size_t evaluateScore(const size_t X, const size_t N) {
	return (N + 1) * (X - 1) * (X - 1);
}

size_t puzzleGame(Grid *grid) {

	size_t playerScore = 0;

	// Remplir toutes les cases de la grille avec des espaces
	for (int i = 0; i < grid->rows; ++i)
		memset(grid->data[i], ' ', grid->columns * sizeof(char));

	// Afficher la grille vide
	gridPrint(grid, playerScore);

	// Remplir aléatoirement la grille
	gridFill(grid);

	// Afficher la nouvelle grille
	gridPrint(grid, playerScore);

	bool running = true;
	while (running) {

		// Actualiser la grille
		gridUpdateBoxes(grid, &playerScore);

		if (gameOver(*grid)) {
			running = false;
			continue;
		}

		//ask for swap
		printf("Choisissez deux cases voisines a echanger\n");

		Coordinate coord1 = {};
		Coordinate coord2 = {};

		/**
		 * Demander la case 1 puis la 2
		 * Si la 2 est invalide, redemander la 1
		 */
		do {
			secureGetCase1(grid, &coord1);
		}while (!secureGetCase2(*grid, coord1, &coord2));


		gridSwapBoxes(grid, coord1, coord2);

		gridPrint(grid, playerScore);

	}

	printf("\nGame over.\n");
	return playerScore;
}