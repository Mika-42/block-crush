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
#include <time.h>
#include <ctype.h>


#include <conio.h>

bool gameOver(Grid grid) {
	const Coordinate directions[4] =
	{
		(Coordinate){+1, 0}, // Bas
		(Coordinate){-1, 0}, // Haut
		(Coordinate){0, +1}, // Droite
		(Coordinate){0, -1}, // Gauche
	};

	// Pour chaque direction
	for (size_t k = 0; k < 4; k++) {
		// Parcourir la grille
		for (size_t i = 0; i < grid.rows; i++) {
			for (size_t j = 0; j < grid.columns; j++) {
				//stocker les coordonnées actuelles
				const Coordinate coordinate = {i, j};

				//stocker les coordonnées de la k-ième direction
				const Coordinate neighbour = {i + directions[k].row, j + directions[k].col};

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

	while (true) {
		// Actualiser la grille
		gridUpdateBoxes(grid, &playerScore);

		if (gameOver(*grid)) {
			break;
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
		} while (!secureGetCase2(*grid, coord1, &coord2));


		gridSwapBoxes(grid, coord1, coord2);

		gridPrint(grid, playerScore);
	}

	return playerScore;
}

size_t rushGame(Grid *grid) {
	size_t playerScore = 0;

	// Remplir toutes les cases de la grille avec des espaces
	for (int i = 0; i < grid->rows; ++i)
		memset(grid->data[i], ' ', grid->columns * sizeof(char));

	// Afficher la grille vide
	gridPrint(grid, playerScore);

	// Remplir toutes les cases de la grille aléatoirement
	gridFill(grid);

	// Conserver que les 3 dernières lignes
	for (int i = 0; i < grid->rows - 3; ++i)
		memset(grid->data[i], ' ', grid->columns * sizeof(char));

	// Afficher la grille
	gridPrint(grid, playerScore);

	// On récupère le temps au lancement de la fonction
	time_t start = time(nullptr);

	bool firstCoordIsValid = false, secondCoordIsValid = false;

	Coordinate coord1 = {ULLONG_MAX, ULLONG_MAX};
	Coordinate coord2 = {ULLONG_MAX, ULLONG_MAX};

	char input2[2] = {}; // Buffer pour la case 1
	char input1[2] = {}; // Buffer pour la case 2
	memset(input1, 0, 2 * sizeof(char));
	memset(input2, 0, 2 * sizeof(char));

	printf("Case 1: ");
	while (true) {
		// Récupération de la case 1

		// Si la première coordonnée est invalide
		if (!firstCoordIsValid) {

			// Demander la première coordonnée
			firstCoordIsValid = nonBlockingSecureGet(grid, input1, &coord1, "Case 1: ");

			// Si elle est valide alors demander la deuxième coordonnée
			if (firstCoordIsValid) {
				printf("Case 2: ");
			}
		}

		// Si la première coordonnée est valide, mais pas la deuxième
		if (firstCoordIsValid && !secondCoordIsValid) {

			// Demander la deuxième coordonnée
			secondCoordIsValid = nonBlockingSecureGet(grid, input2, &coord2, "Case 2: ");

			// Si la deuxième coordonnée est valide
			if (secondCoordIsValid) {

				Grid copy = *grid;
				// On vérifie si la permutation aboutie à une séquence valide
				gridSwapBoxes(&copy, coord1, coord2);
				const Sequence sequence = getLongestSequences(&copy);

				// Si le coup n'est pas jouable, on redemande la case 1
				if (sequence.length == 0) {
					printf("Permutation non valide.\n");
				} else {
					gridSwapBoxes(grid, coord1, coord2);

					// Afficher la grille
					gridPrint(grid, playerScore);

					//Actualiser la grille
					gridUpdateBoxes(grid, &playerScore);
					// Afficher la grille
					gridPrint(grid, playerScore);
					printf("Choisissez deux cases voisines a echanger\n");
				}
				firstCoordIsValid = secondCoordIsValid = false;
				printf("Case 1: ");
			}
		}

		// Vérifier si 15 secondes se sont écoulées
		const time_t current = time(nullptr);

		if (difftime(current, start) >= rushModeTimeInterval_s) {
			secondCoordIsValid = false;
			// Réinitialiser l'entrée utilisateur
			memset(input1, 0, 2 * sizeof(char));
			memset(input2, 0, 2 * sizeof(char));

			start = time(nullptr);

			// Pousser les éléments de la grille vers le haut et insérer une ligne
			bool gameover = gridPushUpInsertBoxes(grid) != SUCCESS;

			// Afficher la grille
			gridPrint(grid, playerScore);

			// Si un élément sort de la grille alors game over
			if (gameover) {
				break;
			}

			// Sinon Actualiser la grille
			gridUpdateBoxes(grid, &playerScore);

			// Afficher la grille
			gridPrint(grid, playerScore);
			printf("Choisissez deux cases voisines a echanger\n");
			printf("Case 1: ");
		}
	}

	return playerScore;
}
