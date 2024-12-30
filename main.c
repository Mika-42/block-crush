#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "grid.h"
#include "userInput.h"

void printMainMenu() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n");
	printf("┃                        MENU PRINCIPAL                        ┃\n");
	printf("┠──────────────────────────────────────────────────────────────┨\n");
	printf("┃ [1] Nouvelle partie                                          ┃\n");
	printf("┃ [2] Voir les meilleurs scores                                ┃\n");
	printf("┃ [3] Règles du jeux                                           ┃\n");
	printf("┃ [4] Quitter                                                  ┃\n");
	printf("┖──────────────────────────────────────────────────────────────┚\n");
}

void printNewGameMenu() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n");
	printf("┃                       NOUVELLE  PARTIE                       ┃\n");
	printf("┠──────────────────────────────────────────────────────────────┨\n");
	printf("┃ [1] Puzzle                                                   ┃\n");
	printf("┃ [2] Rush                                                     ┃\n");
	printf("┃ [3] Revenir au menu principal                                ┃\n");
	printf("┖──────────────────────────────────────────────────────────────┚\n");
}

void printRules() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n");
	printf("┃                        REGLES DU JEU                         ┃\n");
	printf("┠──────────────────────────────────────────────────────────────┨\n");
	printf("┃ [1] Revenir au menu principal                                ┃\n");
	printf("┖──────────────────────────────────────────────────────────────┚\n");
}

void printGridMenu() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n");
	printf("┃                     TAILLE DE  LA GRILLE                     ┃\n");
	printf("┠──────────────────────────────────────────────────────────────┨\n");
	printf("┃ [*] 7 < nombre de colonnes < 13                              ┃\n");
	printf("┃ [*] 3 < nombre de lignes   <  7                              ┃\n");
	printf("┖──────────────────────────────────────────────────────────────┚\n");
}

char readIntInRange(const int min, const int max, const bool display_error, const char* error_msg, void (*error_process)(void)) {

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

		// Ne pas permettre à l'utilisateur de rentrer un signe
		if (buffer[0] == '-' || buffer[0] == '+') {
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
int startMenu();

size_t newGameMenu() {

	const int input = readIntInRange(1, 3, true,">>> Selection: ", printNewGameMenu);
	bool isPuzzle = false;
	switch (input) {
		case 1:
			isPuzzle = true;
			printf("Partie puzzle\n"); break;
		case 2:
			isPuzzle = false;
			printf("Partie rush\n"); break;
		case 3:
			startMenu(); break;
		default:;
	}

	const int col = readIntInRange(8, 12, true,">>> colonnes: ", printGridMenu);
	const int row = readIntInRange(4, 6, true,">>> lignes: ", printGridMenu);

	Grid grid = {col, row};

	return isPuzzle ? puzzleGame(&grid) : 0;
}
int startMenu() {

	const int input = readIntInRange(1, 4, true, ">>> Selection: ", printMainMenu);

	switch (input) {
		case 1:
			newGameMenu(); break;
		case 2:
			printf("Voir les meilleurs scores\n");
			break;
		case 3:

			const int in = readIntInRange(1, 1, true, ">>> Selection: ", printRules);

			break;

		case 4: /*Quitter*/ return 42;
		default: ;
	}

	printf("┎──────────────────────────────────────────────────────────────┒\n");
	printf("┃ [1] Revenir au menu principal                                ┃\n");
	printf("┖──────────────────────────────────────────────────────────────┚\n");
	readIntInRange(1, 1, true, ">>> Selection: ", nullptr);
	return startMenu();
}

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
	srand(42); //time(nullptr)

	return startMenu();
}
