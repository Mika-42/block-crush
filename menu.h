//
// Created by Matis on 30/12/2024.
//

#ifndef MENU_H
#define MENU_H
#include "dataType.h"

//===Print menu==============================================================//

/**
 * @brief		Effacer la console et afficher le menu principal
 */
void printMainMenu();

/**
 * @brief		Effacer la console et afficher le menu de sélection d'une partie
 */
void printNewGameMenu();

/**
 * @brief		Effacer la console et afficher le menu des règles du jeu
 */
void printRules();

/**
 * @brief		Effacer la console et afficher le menu de sélection de la grille
 */
void printGridMenu();

/**
 * @brief		Afficher l'écran de fin de partie
 */
void printGameOver();

/**
 * @brief		Effacer la console et afficher le menu des meilleurs scores
 */
void printBestScore();
//===========================================================================//
/**
 * @brief		Compare deux structures de type UserScore
 *				pour les trier dans l'ordre décroissant
 *
 * @param lhs	structure 1
 * @param rhs	structure 2
 *
 * @return		Renvoie l'écart entre deux scores
 *
 * @see			sortPlayerScore
 */
int compare(const void* lhs, const void* rhs);

/**
 * @brief		Trie dans l'ordre décroissant le score des joueurs
 */
void sortPlayerScore();

/**
 * @brief		Lance le menu des meilleurs scores
 */
void bestScoreMenu();

/**
 * @brief		Demander à l'utilisateur les dimensions de la grille et
 *				afficher les scores correspondent
 */
void askUserScoresByGridSize();

/**
 * @brief		Demander à l'utilisateur un nom, vérifier s'il est enregistré
 *				Si oui afficher son score
 */
void askUserScoresByNameMenu();

/**
 * @brief		Demander à l'utilisateur son nom au début du jeu
 *
 * @param[in]	username Nom d'utilisateur à récupérer
 *
 * @warning		Le paramètre 'username' doit être un tableau de char de taille 20.
 */
void askUsername(char* username);

/**
 * @brief		Lancer le menu principal
 * @param[in]	username Nom du joueur
 *
 * @retval		42 La réponse à La grande question sur la vie,
				l'Univers et le reste dans l’œuvre de Douglas Adams Le Guide du voyageur galactique.
				Il reste alors à déterminer qu'elle était, précisément, la question.
 */
int startMenu(const char* username);

/**
 * @brief		Lancer le menu de sélection du mode de jeu
 *
 * @retval		PUZZLE Mode de jeu puzzle
 * @retval		RUSH Mode de jeu rush
 * @retval		NONE Retour au menu principal
 */
GameMode newGameMenu();

/**
 * @brief		Lancer le menu de sélection de la grille
 *
 * @return		Grille avec les dimensions saisie par l'utilisateur
 */
Grid gridMenu();

#endif //MENU_H
