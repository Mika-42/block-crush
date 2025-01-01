//
// Created by Matis on 29/12/2024.
//

#ifndef GAME_H
#define GAME_H

#include "grid.h"

/**
 * @brief		Détermine la fin de la partie
 *
 * @note		Le paramètre grid est passé par valeur pour avoir
 *				une copie de la grille du jeu pour effectuer des tests.
 *
 * @param[in]	grid Grille du jeu
 *
 * @retval		true Si plus aucune permutation n'aboutit à une séquence viable
 * @retval		false Si au moins une permutation est possible
 */
bool gameOver(Grid grid);

/**
 * @brief		Calcul le score en fonction de la longueur de la séquence supprimée
 *				et du nombre de séquences supprimée en cascade
 *
 * @param[in]	X Longueur de la chaine supprimée
 * @param[in]	N Nombre de séquences préalablement subprime en cascade
 *
 * @return		Score après suppression des séquences
 */
size_t evaluateScore(const size_t X, const size_t N);

/**
 * @brief		Partie en mode Puzzle
 *
 * @note		Le paramètre grid est passé par pointeur
 *				afin d'être modifié au cours de la partie.
 *
 * @param[out]	grid Grille du jeu
 * @return		Score de la partie
 */
size_t puzzleGame(Grid *grid);

/**
 * @brief		Partie en mode Rush
 *
 * @note		Le paramètre grid est passé par pointeur
 *				afin d'être modifié au cours de la partie.
 *
 * @param[out]	grid Grille du jeu
 * @return		Score de la partie
 */
size_t rushGame(Grid *grid);

#endif //GAME_H
