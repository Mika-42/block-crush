#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
	srand(42); //time(nullptr)

	char username[50];
	askUsername(username);


	return startMenu();
}
