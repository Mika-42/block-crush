//
// Created by Matis on 16/12/2024.
//

#ifndef GRID_H
#define GRID_H

#include "dataType.h"

//===Prédicats=====================================================================//
/**
 * @brief		Vérifie si la case [x][y] est vide
 *
 * @note		- Le mot clé 'inline' permet d'optimiser la fonction,
 *				au lieu qu'elle soit appelée sur la pile le compilateur
 *				la remplacera par son expression booléenne.
 *
 * @note		- coord est passé par valeur constante
 *				afin de garantir l'immutabilité des données d'entrées
 *
 * @note		- grid est passé par pointeur constant pour éviter
 *				les copies implicites de la grille qui pourrait être
 *				générée à chaque appel de la fonction
 *
 * @param[in]	grid
 * @param[in]	coord
 *
 * @retval		true
 * @retval		false
 */
bool gridIsEmptyBox(const Grid *grid, const Coordinate coord);

/**
 * @brief		Vérifier si les coordonnées sont dans la grille
 *
 * @note		- Le mot clé 'inline' permet d'optimiser la fonction,
 *				au lieu qu'elle soit appelée sur la pile le compilateur
 *				la remplacera par son expression booléenne.
 *
 * @note		- coord est passé par valeur constante
 *				afin de garantir l'immutabilité des données d'entrées
 *
 * @note		- grid est passé par pointeur constant pour éviter
 *				les copies implicites de la grille qui pourrait être
 *				générée à chaque appel de la fonction
 *
 * @param[in]	grid grille support
 * @param[in]	coord Coordonnées à vérifier
 *
 * @retval		true Si les coordonnées sont dans la grille
 * @retval		false Si les coordonnées ne sont pas dans la grille
 */
bool gridIsValidCoordinate(const Grid *grid, const Coordinate coord);

/**
 * @brief		Vérifier si les coordonnées sont égales
 *
 * @note		- Le mot clé 'inline' permet d'optimiser la fonction,
 *				au lieu qu'elle soit appelée sur la pile le compilateur
 *				la remplacera par son expression booléenne.
 *
 * @note		- coord1 et coord2 sont passé par valeur constante
 *				afin de garantir l'immutabilité des données d'entrées
 *
 * @param[in]	coord1 Coordonnées 1 à comparer
 * @param[in]	coord2 Coordonnées 2 à comparer
 *
 * @retval		true si coord1 = coord2
 * @retval		false si coord1 != coord2
 */
bool coordEquals(const Coordinate coord1, const Coordinate coord2);
//==================================================================================//
/**
 * @brief		Remplir une grille avec les lettres A, O, X, H de manière aléatoire
 *
 * @note		- grid est passé par pointeur constant pour éviter
 *				les copies implicites de la grille qui pourrait être
 *				générée à chaque appel de la fonction
 *
 * @param[out]	grid Structure à remplire
 */
void gridFill(Grid *grid);

/**
* @brief	Affiche une grille dans la console sous la forme
*
*			    A B C D E F G H I J
*			   ┏─┬─┬─┬─┬─┬─┬─┬─┬─┬─┓
*			 1 │ │ │ │ │ │ │ │ │ │ │
*			   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
*			 2 │ │ │ │ │ │ │ │ │ │ │
*			   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
*			 3 │ │ │ │ │ │ │ │ │ │ │
*			   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
*			 4 │ │ │ │ │ │ │ │ │ │ │
*			   ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
*			 5 │ │ │ │ │ │ │ │ │ │ │
*			   ┗─┴─┴─┴─┴─┴─┴─┴─┴─┴─┛
*
* @param[in]	grid structure à afficher
*/
void gridPrint(const Grid *grid);

/**
 * @brief		Vide une case à une certaine position dans le tableau
 *
 * @note		- coord est passé par valeur constante
 *				afin de garantir l'immutabilité des données d'entrées
 *
 * @note		- grid est passé par pointeur constant pour éviter
 *				les copies implicites de la grille qui pourrait être
 *				générée à chaque appel de la fonction
 *
 * @param[out]	grid Grille dans laquelle la case doit être effacée
 * @param[in]	coord Position de la case à effacer
 *
 * @retval		GRID_SIZE_ERROR Tentative d'accès à des données hors du tableau
 * @retval		SUCCESS Tout est ok
 */
ErrorCode gridEmptyBox(Grid *grid, const Coordinate coord);

/**
 * @brief		Échange de place deux cases
 *
 * @note		- coord1 et coord2 sont passé par valeur constante
 *				afin de garantir l'immutabilité des données d'entrées
 *
 * @note		- grid est passé par pointeur afin de manipuler la grille
 *				elle-même et non une copie
 *
 * @param[out]	grid	Grille dans laquelle les cases vont être échangée
 * @param[in]	coord1	position 1
 * @param[in]	coord2	position 2

 * @retval		GRID_SIZE_ERROR Tentative d'accès à des données hors du tableau
 * @retval		SUCCESS Tout est ok
 */
ErrorCode gridSwapBoxes(Grid *grid, const Coordinate coord1, const Coordinate coord2);

/**
 * @brief		Fait tomber les éléments vers le bas de la grille
 *				s'il y a un vide en dessous d'eux
 *
 * @note		Grid est passé par pointeur afin de manipuler la grille
 *				elle-même et non une copie
 *
 * @param[out]	grid Grille à modifier
 */
void gridFallElement(Grid *grid);

/**
 * @brief		Retire dela grille la plus longue séquence
 *
 * @note		Grid est passé par pointeur afin de manipuler la grille
 *				elle-même et non une copie
 *
 * @param[out]	grid Grille dans laquelle retirer la plus longue séquence
 *
 * @return		Taille de la plus longue séquence >= 4 sinon 0
 */
size_t removeLongestSequences(Grid *grid);

/**
 * @brief		Récupère la plus longue séquence dans la grille
 *
 * @note		Cette fonction s'appuie l'algorithme DFS. En effet,
 *				la recherche des voisins est similaire à un parcours
 *				en profondeur dans un graphe.
 *
 *				Exemple:
 *
 *				On considère une séquence de X à deux branches
 *				x1 et x2 qui débute en x0
 *
 *					     A  B  C  D  E  F  G  H  I  J
 *					   ┏──┬──┬──┬──┬──┬──┬──┬──┬──┬──┓
 *					 1 │  │  │  │  │  │  │  │  │  │  │
 *					   ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 *					 2 │  │  │  │x1│x0│x2│x2│x2│  │x2│
 *					   ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 *					 3 │  │  │  │x1│  │  │  │x2│x2│x2│
 *					   ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 *					 4 │  │  │x1│x1│  │  │  │  │  │  │
 *					   ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 *					 5 │  │  │  │  │  │  │  │  │  │  │
 *					   ┗──┴──┴──┴──┴──┴──┴──┴──┴──┴──┛
 *
 *				l'algorithme arrive au 'noeud' x0 et le garde en mémoire
 *				il va parcourir la branche x1, lorsque toute la branche
 *				a été visité, il repart du noeud x0 et parcours la branche x2
 *
 * @param[in]	grid Grille laquelle chercher la plus longue séquence
 *
 * @return		Sequence : structure contenant la plus longue séquence et sa taille
 */
Sequence getLongestSequences(const Grid *grid);

#endif //GRID_H
