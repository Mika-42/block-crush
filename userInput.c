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

#include <stdlib.h>

#include "grid.h"

#include <conio.h>
#include <string.h>

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

Coordinate getInputCoord(const char *msg) {
	// variable temporaire pour récupérer la saisie
	// A1, 1A, 1a, a1
	char coordInput[2];

	while (true) {
		printf("%s", msg);

		// [1] On récupère les deux premiers caractères
		coordInput[0] = (char) getchar();
		coordInput[1] = (char) getchar();

		// [2] S'il y a d'autres caractères dans le tampon
		// On le vide puis on retourne au [1]
		if (getchar() != '\n') {
			while (getchar() != '\n') {
			}
			continue;
		}

		// [3] Si l'entrée utilisateur est valide
		// alors renvoyer les coordonnées converties
		Coordinate coord = {};
		if (strToCoord(coordInput, &coord) == SUCCESS) {
			return coord;
		}
	}
}

void secureGetCase1(const Grid *grid, Coordinate *coord) {
	while (true) {
		*coord = getInputCoord("Case 1: ");

		if (!gridIsValidCoordinate(grid, *coord)) {
			printf("Coordonnées invalides.\n");
			continue;
		}
		if (gridIsEmptyBox(grid, *coord)) {
			printf("Choisissez une case non-vide.\n");
			continue;
		}

		break;
	}
}

bool secureGetCase2(Grid grid, const Coordinate coord1, Coordinate *coord2) {
	while (true) {
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

		break;
	}
	return true;
}

int readIntInRange(int min, int max, const bool display_error, const char *error_msg,
                   void (*error_process)(void)) {
	// Si min > max alors les inverser
	if (min > max) {
		min ^= max;
		max ^= min;
		min ^= max;
	}

	if (error_process != nullptr) error_process();
	if (display_error) printf(error_msg);

	while (true) {
		char buffer[100];

		// Lire toute la ligne du tampon d'entrée
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			if (error_process != nullptr) error_process();
			if (display_error) printf(error_msg);
			continue;
		}

		// Ne pas permettre à l'utilisateur de rentrer le signe +
		if (buffer[0] == '+') {
			if (error_process != nullptr) error_process();
			if (display_error) printf(error_msg);
			continue;
		}

		// On vérifie si l'entrée est un nombre en base 10.
		char *end;
		const int value = strtol(buffer, &end, 10);

		// On va vérifier si l'entrée est invalide
		if (end == buffer || *end != '\n') {
			if (error_process != nullptr) error_process();
			if (display_error) printf(error_msg);
			continue;
		}

		// Vérification de l'intervalle
		if (value < min || value > max) {
			if (error_process != nullptr) error_process();
			if (display_error) printf(error_msg);
			continue;
		}

		return value;
	}
}

bool getKeyboardInput(char *input) {

	// On déclare ces 3 variables 'static' pour qu'elles
	// ne soient pas réinitialisé à chaque appel de la fonction

	//Signale si une touche a été touchée précédemment
	static bool hitted = false;

	// L'indice est un booléen, car on souhaite faire osciller l'indice entre 0 et 1.
	static bool index = 0;

	// Tampon d'entrée qui représente une saisie de 2 caractères
	static char entry[2];

	// Si une touche du clavier est appuyée
	if (_kbhit()) {

		// Récupération du caractère associé à la touche
		entry[index] = (char) _getch();

		// Si cette touche n'était déjà pas appuyée
		if (!hitted) {

			// On la signale comme ayant été appuyé
			hitted = true;

			// On affiche le caractère correspondant
			printf("%c", entry[index]);

			// On passe au prochain caractère de manière cyclique
			index = !index;
		}
	}
	// Si une touche n'a pas été appuyé
	else {
		// On signale son état
		hitted = false;
	}

	// Si le tampon d'entrée est rempli
	if (entry[0] != 0 && entry[1] != 0) {

		// On transfert son contenu à notre paramètre d'entrée 'input'
		input[0] = entry[0];
		input[1] = entry[1];

		// On vide le tampon
		memset(entry, 0, sizeof(char) * 2);

		// On se replace au début du tampon
		index = 0;

		return true;
	}
	return false;
}

bool nonBlockingSecureGet(const Grid *grid, char input[2], Coordinate *coord, const char *msg) {

	// On récupère la saisie utilisateur
	const bool isFull = getKeyboardInput(input);

	// Si la saisie est complete
	if (isFull) {

		printf("\n");

		if (strToCoord(input, coord) != SUCCESS || !gridIsValidCoordinate(grid, *coord)) {
			printf("Coordonnées invalides.\n");
		} else if (gridIsEmptyBox(grid, *coord)) {
			printf("Choisissez une case non-vide.\n");
		} else {
			memset(input, 0, 2 * sizeof(char));
			return true;
		}

		// Réinitialisation du tampon d'entrée
		memset(input, 0, 2 * sizeof(char));

		printf(msg);
	}
	return false;
}
