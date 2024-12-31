//
// Created by Matis on 29/12/2024.
//

#ifndef USERINPUT_H
#define USERINPUT_H

#include "dataType.h"

/**
 * @brief 		Convertir une entrée utilisateur sous forme de coordonnées
 *
 *				Exemple :
 *					"A1", "a1", "1A", "1a" → (0, 0)
 *					"B6", "6B", "6b", "b6" → (5, 1)
 *
 * @param[in]	in_coord Coordonnées sous forme de texte (une lettre, un chiffre)
 * @param[out]	coordinate Coordonnées de sortie
 *
 * @retval		SUCCESS Tout est ok
 * @retval		GENERIC_ERROR Le format d'entrée attendu
 */
ErrorCode strToCoord(const char in_coord[2], Coordinate *coordinate);

/**
 * @brief		Affiche un message, récupérer une saisie utilisateur
 *				et la convertir en coordonnées
 *
 * @param[in]	msg Message à afficher avant la saisie utilisateur
 *
 * @return		Coordonnées d'entrée converti en structure
 *
 * @see			strToCoord
 */
Coordinate getInputCoord(const char *msg);

/**
 * @brief		Récupération sécurisée de la coordonnée 1
 *
 * @note		Le paramètre grid est passé par pointeur constant pour
 *				ne pas générer de copie et ne pas risque de modifier la grille.
 *
 * @note		Le paramètre coord est passé par pointeur pour récupérer les données de sorties.
 *
 * @param[in]	grid Grille support
 * @param[out]	coord Coordonnées de sortie
 *
 * @see			getInputCoord
 */
void secureGetCase1(const Grid *grid, Coordinate *coord);

/**
 * @brief		Récupération sécurisée des coordonnées de la 2ᵉ case
 *
 * @note		On passe la grille par valeur afin d'obtenir une copie
 *				qu'on pourra modifier à souhait pour effectuer
 *				les vérifications sans craindre d'endommager la grille principale.
 *
 * @param[in]	grid Copie de la grille à manipuler
 * @param[in]	coord1 Coordonnée 1
 * @param[out]	coord2 Coordonnée 2 voisine de la première
 *
 * @retval		true Si la coordonnée 2 est valide par rapport à la coordonnée 1
 * @retval		false Si la coordonnée 2 invalide par rapport à la coordonnée 1
 *
 * @see			getInputCoord
 */
bool secureGetCase2(Grid grid, const Coordinate coord1, Coordinate *coord2);

/**
 * @brief		Récupère un entier par saisi utilisateur dans un intervalle [min, max]
 *
 * @note		Le type 'void (*error_process)(void)' désigne un pointeur
 *				sur une fonction avec un type de retour 'void' qui prend
 *				en paramètre un 'void'. Toutes les fonctions dont le prototype
 *				se présentant sous la forme 'void f(void);' peuvent être passé à
 *				ce pointeur. Ainsi, on peut appeler une fonction différente selon
 *				la manière dont on souhaite gérer les erreurs.
 *
 * @param[in]	min Valeur minimale
 * @param[in]	max Valeur maximale
 * @param[in]	display_error Indique si le message d'erreur doit être affichée
 * @param[in]	error_msg Message d'erreur à afficher
 * @param[in]	error_process Fonction à appeler en cas d'erreur
 *
 * @return		Renvoie la valeur numérique saisie par l'utilisateur
 */
int readIntInRange(int min, int max, const bool display_error, const char *error_msg,
                    void (*error_process)(void));

// todo comment
bool ValidNonBlockingSecureGet(const Grid * grid, char input[2], Coordinate *coord);

bool nonBlockingSecureGet(const Grid *grid, char input[2], Coordinate *coord,const char* msg, const bool skip);
#endif //USERINPUT_H
