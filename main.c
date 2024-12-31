#include <pthread.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"
#include "score.h"

int main(void) {

	// TODO
	SetConsoleOutputCP(CP_UTF8);
	srand(42); //time(nullptr)
	char username[20];
	readUserScore();
	askUsername(username);
	return startMenu(username);;
}
