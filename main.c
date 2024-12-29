#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
	size_t result = 0, ret = 0;

	while ((ret = removeSeqWithScore(grid))){
	result += ret;
	gridPrint(grid);
	gridFallElement(grid);
	gridPrint(grid);
	}
	return result;
}

bool gameOver(const Grid *grid) {

	const Coordinate directions[4] =
	{
		(Coordinate){+1,0},
		(Coordinate){-1,0},
		(Coordinate){0,+1},
		(Coordinate){0,-1},
	};

	Grid copy = *grid;

	for (size_t k = 0; k < 4; k++) {
		for (size_t i = 0; i < copy.rows; i++) {
			for (size_t j = 0; j < copy.columns; j++) {

				const Coordinate coordinate = {i,j};
				const Coordinate neighbour = {i + directions[k].row,j + directions[k].col };

				if (!gridIsValidCoordinate(&copy, neighbour) ||
					gridIsEmptyBox(&copy, neighbour) ||
					gridIsEmptyBox(&copy, coordinate)) {
					continue;
				}

				gridSwapBoxes(&copy, neighbour, coordinate);
				const Sequence sequence = getLongestSequences(&copy);
				gridSwapBoxes(&copy, neighbour, coordinate);

				if (sequence.length != 0) {
					return false;
				}
			}
		}
	}
	return true;
}



Coordinate getInputCoord(const char* msg) {
	char coordInput[3];
	Coordinate coord= {};

	do {
		printf("%s", msg);
		scanf("%2s", coordInput);
		fflush(stdin);

	}
	while (strToCoord(coordInput, &coord) != SUCCESS);

	return coord;
}

bool isNeighbour(const Coordinate coord, const Coordinate neighbour) {
	const bool neighbourLeft = coord.row - 1 == neighbour.row && coord.col == neighbour.col;
	const bool neighbourRight = coord.row + 1 == neighbour.row && coord.col == neighbour.col;
	const bool neighbourTop = coord.row == neighbour.row && coord.col - 1 == neighbour.col;
	const bool neighbourBottom = coord.row == neighbour.row && coord.col + 1 == neighbour.col;

	return neighbourLeft || neighbourRight || neighbourTop || neighbourBottom;
}
size_t puzzleGame(Grid *grid) {

	size_t playerScore = 0;


	gridPrint(grid);

	gridFill(grid);
	gridPrint(grid);

	bool running = true;
	while (running) {

		playerScore += updateBoxes(grid);

		if (gameOver(grid)) {
			running = false;
		}

		//ask for swap
		printf("Choisissez deux cases voisines a echanger\n");

		Coordinate coord1 = {};
		Coordinate coord2 = {};

		bool looping = true;
		while (looping)
		{
			coord1 = getInputCoord("Case 1: ");

			if (!gridIsValidCoordinate(grid, coord1)) {
				printf("Coordonnées invalides.\n");
				continue;
			}
			if (gridIsEmptyBox(grid, coord1)) {
				printf("Choisissez une case non-vide.\n");
				continue;
			}

			looping = false;
		}

		looping = true;
		while (looping)
		{
			/* todo si le swap des deux coords ne donne pas une chaine, l'interdire*/
			coord2 = getInputCoord("Case 2: ");

			if (!gridIsValidCoordinate(grid, coord2)) {
				printf("Coordonnées invalides.\n");
				continue;
			}

			if (gridIsEmptyBox(grid, coord2)) {
				printf("Choisissez une case non-vide.\n");
				continue;
			}

			if (!isNeighbour(coord1, coord2)) {
				printf("Choisissez une case adjacente a la premiere.\n");
				continue;
			}

			gridSwapBoxes(grid, coord1, coord2);
			const Sequence sequence = getLongestSequences(grid);
			gridSwapBoxes(grid, coord1, coord2);

			if (sequence.length == 0) {
				printf("Permutation non valide.\n");
				continue; //go to coord1
			}

			looping = false;

		}

		gridSwapBoxes(grid, coord1, coord2);

		gridPrint(grid);

	}
	return playerScore;
}

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
	srand(42); //time(nullptr)
	//
	// startMenu();
	//
	Grid grid = {12, 6, {}};
	for (int i = 0; i < grid.rows; ++i)
		memset(grid.data[i], ' ', grid.columns * sizeof(char));


	const size_t scorePlayer = puzzleGame(&grid);

	printf("\n\nscore: %llu", scorePlayer);

	getchar();
	return 42;
}
