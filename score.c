//
// Created by Matis on 30/12/2024.
//

#include "score.h"

#include <stdio.h>
#include <string.h>

const char* FILE_SCORE_NAME = "score.txt";

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
	// S'il existe déjà alors modifier son score
	else {
		if (usr_score.score > user_score[userID].score) {
			user_score[userID] = usr_score;
		}
	}
}

// return the index of user
int userExist(const char* username) {
	for (int i = 0; i < MaxPlayers; i++) {
		if (strcmp(user_score[i].username, username) == 0) {
			return i;
		}
	}
	return -1;
}

UserScore* getUserScore() {
	return user_score;
}

int newUsernameIndex() {
	for (int i = 0; i < MaxPlayers; i++) {
		if (user_score[i].username[0] == '\0') {
			return i;
		}
	}
	return MaxPlayers;
}

void readUserScore() {
	FILE* file = fopen(FILE_SCORE_NAME, "rb");
	fread(user_score, sizeof(UserScore), MaxPlayers, file);
}

void writeScore() {
	FILE* file = fopen(FILE_SCORE_NAME, "wb");

	if (file == NULL) {
		printf("Error opening file for writing\n");
		return;
	}

	fwrite(user_score, sizeof(UserScore), MaxPlayers, file);

}
