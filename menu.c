//
// Created by Matis on 30/12/2024.
//

#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
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
	// TODO COMPLETER LES REGLES DU JEU
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

//===========================================================================//

int startMenu() {
	// TODO WRITE SCORE TO FILE

	const int input = readIntInRange(1, 4, true, ">>> Selection: ", printMainMenu);

	if (input == 1) {
		const GameMode mode = newGameMenu();

		if (mode != NONE) {
			// commencer une partie

			Grid grid = gridMenu();

			const size_t score = mode == PUZZLE ? puzzleGame(&grid) : 0 /*rushGame*/;
			// todo write score to file
			printGameOver();
			readIntInRange(1, 1, true, ">>> Selection: ", nullptr);
		}
	}

	if (input == 2) {
		printf("Voir les meilleurs scores\n");
	}

	// Afficher les règles
	if (input == 3) {
		readIntInRange(1, 1, true, ">>> Selection: ", printRules);
	}

	// Quitter
	if (input == 4) {
		return 42;
	}

	return startMenu();
}

GameMode newGameMenu() {
	const int input = readIntInRange(1, 3, true, ">>> Selection: ", printNewGameMenu);

	if (input == 1) return PUZZLE;
	if (input == 2) return RUSH;

	return NONE;
}

Grid gridMenu() {
	const int col = readIntInRange(8, 12, true, ">>> colonnes: ", printGridMenu);
	const int row = readIntInRange(4, 6, true, ">>> lignes: ", printGridMenu);
	return (Grid){col, row};
}
