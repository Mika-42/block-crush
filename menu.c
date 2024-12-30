//
// Created by Matis on 30/12/2024.
//

#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "score.h"
#include "userInput.h"

//===Print menu==============================================================//

void printMainMenu() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n"
		   "┃                        MENU PRINCIPAL                        ┃\n"
		   "┠──────────────────────────────────────────────────────────────┨\n"
		   "┃ [1] Nouvelle partie                                          ┃\n"
		   "┃ [2] Voir les meilleurs scores                                ┃\n"
		   "┃ [3] Règles du jeux                                           ┃\n"
		   "┃ [4] Quitter                                                  ┃\n"
		   "┖──────────────────────────────────────────────────────────────┚\n");
}

void printNewGameMenu() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n"
	       "┃                       NOUVELLE  PARTIE                       ┃\n"
	       "┠──────────────────────────────────────────────────────────────┨\n"
	       "┃ [1] Puzzle                                                   ┃\n"
	       "┃ [2] Rush                                                     ┃\n"
	       "┃ [3] Revenir au menu principal                                ┃\n"
	       "┖──────────────────────────────────────────────────────────────┚\n");
}

void printRules() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n"
	       "┃                        REGLES DU JEU                         ┃\n"
		   "┠──────────────────────────────────────────────────────────────┨\n"
		   "┃ Sur une grille 2D de taille allant de 8x4 à 12x6, des        ┃\n"
		   "┃ lettres A,O,H,X sont présentes                               ┃\n"
		   "┃ (une lettre par case de la grille)                           ┃\n"
		   "┃                                                              ┃\n"
		   "┃ L’objectif est de permuter des lettres 2 par 2               ┃\n"
		   "┃ afin de créer des chaînes de 4 lettres identiques se         ┃\n"
		   "┃ touchant verticalement ou horizontalement                    ┃\n"
		   "┃                                                              ┃\n"
		   "┃ M O D E ~ P U Z Z L E                                        ┃\n"
		   "┃                                                              ┃\n"
		   "┃ En mode Puzzle la grille est entièrement remplie de façon    ┃\n"
		   "┃ aléatoire. Le joueur choisi ensuite deux cases               ┃\n"
		   "┃ côtes à côte à permuter (horizontalement ou verticalement).  ┃\n"
		   "┃ La permutation doit obligatoirement créer                    ┃\n"
		   "┃ une chaîne de 4 lettres identiques continues.                ┃\n"
		   "┃                                                              ┃\n"
		   "┃ Lorsque 4 lettres identiques continues ou plus               ┃\n"
		   "┃ sont présentes, elles disparaissent de la grille et          ┃\n"
		   "┃ les lettres qui se trouvaient au-dessus tombent.             ┃\n"
		   "┃                                                              ┃\n"
		   "┃ M O D E ~ R U S H                                            ┃\n"
		   "┃                                                              ┃\n"
		   "┃ En mode rush le fonctionnement est similaire, mais :         ┃\n"
		   "┃ A l’initialisation du jeu, seules les trois lignes du bas    ┃\n"
		   "┃ sont remplies. Toutes les 15 secondes, une nouvelle ligne    ┃\n"
		   "┃ apparaît en bas et pousse les autres lignes vers le haut     ┃\n"
		   "┃ La partie est terminée dès qu’une lettre est poussée hors    ┃\n"
		   "┃ de la grille vers le haut.                                   ┃\n"
		   "┃                                                              ┃\n"
		   "┃                                                              ┃\n"
		   "┃                                                              ┃\n"
		   "┃ [1] Revenir au menu principal                                ┃\n"
		   "┖──────────────────────────────────────────────────────────────┚\n");
}

void printGridMenu() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n"
	       "┃                     TAILLE DE  LA GRILLE                     ┃\n"
	       "┠──────────────────────────────────────────────────────────────┨\n"
	       "┃ [*] nombre de colonnes entre [8, 12]                         ┃\n"
	       "┃ [*] nombre de lignes   entre [4,  6]                         ┃\n"
	       "┖──────────────────────────────────────────────────────────────┚\n");
}

void printGameOver() {
	printf("┎──────────────────────────────────────────────────────────────┒\n"
		   "┃                          GAME OVER                           ┃\n"
		   "┠──────────────────────────────────────────────────────────────┨\n"
		   "┃ [1] Revenir au menu principal                                ┃\n"
		   "┖──────────────────────────────────────────────────────────────┚\n");
}

void printBestScore() {
	system("cls");

	printf("┎──────────────────────────────────────────────────────────────┒\n"
		   "┃                      MEILLEURS  SCORES                       ┃\n"
		   "┠──────────────────────────────────────────────────────────────┨\n"
		   "┃ [1] Rechercher par utilisateur                               ┃\n"
		   "┃ [2] Rechercher par taille de grille                          ┃\n"
		   "┃ [3] Revenir au menu principal                                ┃\n"
		   "┖──────────────────────────────────────────────────────────────┚\n");

}

//===========================================================================//

// Fonction de comparaison pour trier en ordre décroissant
/**
 * lhs => left hand side
 * rhs => right hand side
 */
int compare(const void* lhs, const void* rhs) {
	const auto a = (UserScore*)lhs;
	const auto b = (UserScore*)rhs;
	return b->score - a->score; // Inverser l'ordre pour décroissant
}

void sortPlayerScore() {
	//trier la liste par score décroissant
	qsort(getUserScore(), MaxPlayers, sizeof(UserScore), compare);
}

void bestScoreMenu() {
	// Demander un chiffre en 1 et 3
	const int scoreInput  = readIntInRange(1, 3, true, ">>> Selection: ", printBestScore);

	if(scoreInput == 1) {
		askUserScoresByNameMenu();
		bestScoreMenu();
	}
	if(scoreInput == 2) {
		askUserScoresByGridSize();
		bestScoreMenu();
	}
}

void askUserScoresByGridSize() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n"
		   "┃               RECHERCHER PAR TAILLE DE GRILLE                ┃\n"
		   "┖──────────────────────────────────────────────────────────────┚\n");

	// Demander le nombre de colonnes de la grille
	const size_t col = readIntInRange(8, 12, true, ">>> colonnes: ", nullptr);

	// Demander le nombre de lignes de la grille
	const size_t row = readIntInRange(4, 6, true, ">>> lignes: ", nullptr);

	bool find = false;
	sortPlayerScore();

	for (int i = 0; i < MaxPlayers; ++i) {

		// Vérifier si les dimensions correspondent à une grille précédemment jouée.
		if (getUserScore()[i].gridCol == col && getUserScore()[i].gridRow == row)
		{
			printf("score de %s: %u\n", getUserScore()[i].username, getUserScore()[i].score);
			find = true;
		}
	}

	if (!find) {
		printf("Aucune grille correspondante.\n");
	}

	printf("┎──────────────────────────────────────────────────────────────┒\n"
		   "┃ [1] Revenir au menu meilleures scores                        ┃\n"
		   "┖──────────────────────────────────────────────────────────────┚\n");
	readIntInRange(1, 1, true, ">>> Selection: ", nullptr);
}

void askUserScoresByNameMenu() {
	system("cls");
	printf("┎──────────────────────────────────────────────────────────────┒\n"
	       "┃               RECHERCHER PAR NOM D'UTILISATEUR               ┃\n"
	       "┖──────────────────────────────────────────────────────────────┚\n");

	// Demander un nom d'utilisateur
	printf(">>> ");
	char username[20];

	// On spécifie que l'on souhaite récupérer 20 caractères
	scanf("%20s", username);

	// Vider le tampon d'entrée
	while (getchar() != '\n'){}

	const int usrIndex = userExist(username);

	if (usrIndex < 0) {
		printf("Cet utilisateur n'est pas enregistré.\n");
	}
	else {
		printf("score de %s: %u\n", username, getUserScore()[usrIndex].score);
	}

	printf("┎──────────────────────────────────────────────────────────────┒\n"
	       "┃ [1] Revenir au menu meilleures scores                        ┃\n"
	       "┖──────────────────────────────────────────────────────────────┚\n");
	readIntInRange(1, 1, true, ">>> Selection: ", nullptr);
}

void askUsername(char* username) {
	printf("┎──────────────────────────────────────────────────────────────┒\n"
		   "┃                     NOM DE L'UTILISATEUR                     ┃\n"
		   "┖──────────────────────────────────────────────────────────────┚\n");

	printf(">>> ");
	// On spécifie que l'on souhaite récupérer 20 caractères
	scanf("%20s", username);
}

int startMenu(const char* username) {
	// TODO Call rush Game

	// Demander un chiffre entre 1 et 4
	const int input = readIntInRange(1, 4, true, ">>> Selection: ", printMainMenu);

	if (input == 1) {
		const GameMode mode = newGameMenu();

		if (mode != NONE) {
			// Commencer une partie

			// Créer la grille
			Grid grid = gridMenu();

			// Récupération du score et des dimensions de la grille
			UserScore score = {
				.username = "",
				.score = mode == PUZZLE ? puzzleGame(&grid) : 0 /*rushGame*/,
				.gridCol = grid.columns,
				.gridRow = grid.rows,
			};

			// copie du nom d'utilisateur dans la structure
			strcpy(score.username, username);

			// Écrire le score dans le fichier
			setUserScore(score);
			writeScore();

			printGameOver();
			readIntInRange(1, 1, true, ">>> Selection: ", nullptr);
		}
	}

	// Afficher le menu des scores
	if (input == 2) {
		bestScoreMenu();
	}

	// Afficher les règles
	if (input == 3) {
		readIntInRange(1, 1, true, ">>> Selection: ", printRules);
	}

	// Quitter
	if (input == 4) {
		return 42;
	}

	return startMenu(username);
}

GameMode newGameMenu() {
	// Saisir un chiffre entre 1 et 3
	const int input = readIntInRange(1, 3, true, ">>> Selection: ", printNewGameMenu);

	if (input == 1) return PUZZLE;
	if (input == 2) return RUSH;

	return NONE;
}

Grid gridMenu() {

	// Demander un chiffre en 8 et 12
	const int col = readIntInRange(8, 12, true, ">>> colonnes: ", printGridMenu);
	// Demander un chiffre entre 4 et 6
	const int row = readIntInRange(4, 6, true, ">>> lignes: ", printGridMenu);

	return (Grid){col, row};
}
