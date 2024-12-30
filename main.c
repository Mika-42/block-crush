#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"
#include "score.h"

int main(void) {
	char username[20];

	SetConsoleOutputCP(CP_UTF8);
	srand(42); //time(nullptr)

	readUserScore();
	askUsername(username);

	return startMenu(username);
}
