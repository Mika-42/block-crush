//
// Created by Matis on 30/12/2024.
//

#ifndef SCORE_H
#define SCORE_H

#include "dataType.h"

/**
 * @brief		Modifie la valeur du score d'un joueur
 *				si celui-ci est meilleur que le précédent
 *
 * @param[in]	usr_score Données relatives au score du joueur
 */
void setUserScore(const UserScore usr_score);

/**
 * @brief		Vérifie si un utilisateur est présent dans la liste des scores
 * @param		username Nom de l'utilisateur à rechercher
 *
 * @return		S'il existe, l'indice du joueur dans le tableau
 * @retval		-1 Si le joueur n'est pas dans le tableau
 */
int userExist(const char* username);

/**
 * @brief		Permet d'accéder au tableau des scores
 *
 * @return		Renvoie un pointeur sur le tableau de joueur déclaré
 *				en local pour le modifier depuis d'autres fichiers
 */
UserScore* getUserScore();

/**
 * @brief		Permet d'obtenir le premier emplacement vide pour le score
 *
 * @return		Renvoi l'indice de la première case vide dans le tableau des scores
 * @retval		MaxPlayers Est renvoyé si plus aucune case n'est disponible
 */
int newUsernameIndex();

/**
 * @brief		Écrire le tableau des scores
 */
void writeScore();

/**
 * @brief		Récupérer les sores dans le tableau
 */
void readUserScore();
#endif //SCORE_H
