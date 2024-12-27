#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grid.h"

void newParty() {
}

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
		case 1: newParty(); break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
}

size_t score(const size_t X, const size_t N) {
 return (N + 1) * (X - 1) * (X - 1);
}

size_t deleted = 0;
size_t removeSeqWithScore(Grid *grid) {
	size_t ret = 0;
	size_t scoring = 0;
	while ((ret = removeLongestSequences(grid))) {
		scoring += score(ret, deleted);
		deleted++;
		gridPrint(grid);
	}
	return scoring;
}

size_t updateBoxes(Grid *grid) {
	size_t result = 0;

	result += removeSeqWithScore(grid);
	gridFallElement(grid);
	gridPrint(grid);
	result += removeSeqWithScore(grid);

	return result;
}

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
	srand(42); //time(nullptr)
	//
	// startMenu();
	//
	Grid grid = {10, 5};

	gridFill(&grid);


	size_t step = 0;
	gridPrint(&grid);

	while (1) {};

	size_t result = 0;

	result += updateBoxes(&grid);

	swapBoxes(&grid, (Coordinate){0, 4}, (Coordinate){1, 4});
	gridPrint(&grid);

	result += updateBoxes(&grid);

	swapBoxes(&grid, (Coordinate){3, 0}, (Coordinate){2, 0});
	gridPrint(&grid);

	result += updateBoxes(&grid);

	swapBoxes(&grid, (Coordinate){2, 3}, (Coordinate){3, 3});
	gridPrint(&grid);

	result += updateBoxes(&grid);

	swapBoxes(&grid, (Coordinate){4, 0}, (Coordinate){3, 0});
	gridPrint(&grid);

	result += updateBoxes(&grid);

	printf("\n\nscore: %llu\n", result);

	getchar();
	return 42;
}
