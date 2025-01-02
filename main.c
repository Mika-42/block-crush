#include <pthread.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"
#include "score.h"

void setupGame() {

	// Active l'affichage de l'UTF-8 dans la console Windows
	SetConsoleOutputCP(CP_UTF8);

	// Génération d'une seed aléatoire
	srand(time(nullptr));
}

int startGame() {
	char username[20];

	// Récupération des scores dans le fichier
	readUserScore();

	askUsername(username);
	return startMenu(username);
}

int main(void) {

	setupGame();
	return startGame();

}