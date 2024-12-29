#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "grid.h"
#include "userInput.h"

void printMenu() {
	printf("+-------------------------------+\n");
	printf("|           GAME MENU           |\n");
	printf("+-------------------------------+\n");
	printf("| [1] Nouvelle partie           |\n");
	printf("| [2] Voir les meilleurs scores |\n");
	printf("| [3] Quitter                   |\n");
	printf("+-------------------------------+\n");
}

int secureGet(const char* msg, int* value) {
	char input[100];

	printf("%s", msg);

	if (fgets(input, sizeof(input), stdin) == nullptr) {
		return 1;
	}

	errno = 0;
	char* endptr = nullptr;
	const long result = strtol(input, &endptr, 10);

	if (endptr == input) {
		return 1;
	}
	if (errno == ERANGE && (result == LONG_MAX || result == LONG_MIN)) {
		return 1;
	}
	if (*endptr != '\n' && *endptr != '\0') {
		return 1;
	}

	*value = (int)result;

	return 0;
}

int startMenu() {
	printMenu();

	int input = 0;
	while (input < 1 || input > 3) {
		secureGet("Selection: ", &input);
	}
	return input;
}

void runGame() {
	const int menu = startMenu();

	switch (menu) {
		case 1: break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
}



int main(void) {
	SetConsoleOutputCP(CP_UTF8);
	srand(42); //time(nullptr)
	//
	// startMenu();
	//
	Grid grid = {5, 5, {}};

	const size_t scorePlayer = puzzleGame(&grid);
	(void)scorePlayer;
	getchar();
	return 42;
}
