//
// Created by Matis on 30/12/2024.
//

#include "score.h"

#include <stdio.h>

void writeScore(const char* username, size_t score) {
	FILE* file = fopen(FILE_SCORE_NAME, "w");

	if (file == NULL) {
		printf("Error opening file for writing\n");
		return;
	}

	fprintf(file, "%s%d\n", username, score);
}
