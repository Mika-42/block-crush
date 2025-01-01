//
// Created by Matis on 30/12/2024.
//

#include "score.h"

#include <stdio.h>
#include <string.h>

// Nom du fichier score
// .42, la réponse à La grande question sur la vie...
const char *FILE_SCORE_NAME = "score.42";

// tableau contenant tous les joueurs
UserScore user_score[MaxPlayers] = {};

void setUserScore(const UserScore usr_score) {
	const int userID = userExist(usr_score.username);

	// Si le nom d'utilisateur n'existe pas, l'ajouter avec le score
	if (userID < 0) {
		const int index = newUsernameIndex();
		if (index != MaxPlayers) {
			user_score[index] = usr_score;
		}
	}
	// S'il existe déjà et que le score actuel est meilleur
	// que le précédent, alors le modifier
	else {
		if (usr_score.score > user_score[userID].score) {
			user_score[userID] = usr_score;
		}
	}
}

int userExist(const char *username) {
	for (int i = 0; i < MaxPlayers; i++) {
		// Vérifier si deux chaînes de caractères sont égales
		if (strcmp(user_score[i].username, username) == 0) {
			return i;
		}
	}
	return -1;
}

UserScore *getUserScore() {
	return user_score;
}

int newUsernameIndex() {
	for (int i = 0; i < MaxPlayers; i++) {
		//renvoyer l'indice correspondant à la première chaîne de caractère vide
		if (user_score[i].username[0] == '\0') {
			return i;
		}
	}
	return MaxPlayers;
}

void readUserScore() {
	FILE *file = fopen(FILE_SCORE_NAME, "rb");
	fread(user_score, sizeof(UserScore), MaxPlayers, file);
	fclose(file);
}

void writeScore() {
	FILE *file = fopen(FILE_SCORE_NAME, "wb");
	fwrite(user_score, sizeof(UserScore), MaxPlayers, file);
	fclose(file);
}
