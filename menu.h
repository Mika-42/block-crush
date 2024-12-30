//
// Created by Matis on 30/12/2024.
//

#ifndef MENU_H
#define MENU_H
#include "dataType.h"

//===Print menu==============================================================//

/**
 * @brief Effacer la console et afficher le menu principal
 */
void printMainMenu();

/**
 * @brief Effacer la console et afficher le menu de sélection d'une partie
 */
void printNewGameMenu();

/**
 * @brief Effacer la console et afficher le menu des règles du jeu
 */
void printRules();

/**
 * @brief Effacer la console et afficher le menu de sélection de la grille
 */
void printGridMenu();

/**
 * @brief Afficher l'écran de fin de partie
 */
void printGameOver();

/**
 *
 * @param username
 *
 * @warning 'username' doit être un tableau de char de taille 20
 */
void askUsername(char* username);

void askUserScoresByGridSize();

void askUserScoresByNameMenu();
//===========================================================================//

// todo add description
int startMenu(const char* username);

// todo add description
GameMode newGameMenu();

// todo add description
Grid gridMenu();

#endif //MENU_H
