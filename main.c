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

int score(const int X, const int N) {
 return (N + 1) * (X - 1) * (X - 1);
}

int main(void) {
	// srand(42); //time(nullptr)
	//
	// startMenu();
	//
	Grid grid = {10, 5};
	//
	gridFill(&grid);
	//

	size_t step = 0;
	printf("\nstep %llu----------------------\n", ++step);
	gridPrint(&grid);


	while (removeLongestSequences(&grid) != 0) {
		printf("\nstep %llu----------------------\n", ++step);
		gridPrint(&grid);
	}

	printf("\nstep %llu----------------------\n", ++step);
	gridFallElement(&grid);
	gridPrint(&grid);

	printf("\nstep %llu----------------------\n", ++step);
	swapBoxes(&grid, (Coordinate){3, 5}, (Coordinate){3, 6});
	gridPrint(&grid);

	printf("\nstep %llu----------------------\n", ++step);
	removeLongestSequences(&grid);
	gridPrint(&grid);

	printf("\nstep %llu----------------------\n", ++step);
	gridFallElement(&grid);
	gridPrint(&grid);

	printf("\nstep %llu----------------------\n", ++step);
	swapBoxes(&grid, (Coordinate){4, 6}, (Coordinate){4, 7});
	gridPrint(&grid);

	printf("\nstep %llu----------------------\n", ++step);
	removeLongestSequences(&grid);
	gridPrint(&grid);

	printf("\nstep %llu----------------------\n", ++step);
	gridFallElement(&grid);
	gridPrint(&grid);

	printf("\nstep %llu----------------------\n", ++step);
	swapBoxes(&grid, (Coordinate){2, 2}, (Coordinate){3, 2});
	gridPrint(&grid);

	printf("\nstep %llu----------------------\n", ++step);
	removeLongestSequences(&grid);
	gridPrint(&grid);

	printf("\nstep %llu----------------------\n", ++step);
	gridFallElement(&grid);
	gridPrint(&grid);

	return 42;
}
