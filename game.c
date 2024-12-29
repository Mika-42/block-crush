//
// Created by Matis on 29/12/2024.
//

#include "game.h"

bool gameOver(Grid grid) {

	const Coordinate directions[4] =
	{
		(Coordinate){+1,0}, // Bas
		(Coordinate){-1,0}, // Haut
		(Coordinate){0,+1}, // Droite
		(Coordinate){0,-1}, // Gauche
	};

	// Pour chaque direction
	for (size_t k = 0; k < 4; k++) {

		// Parcourir la grille
		for (size_t i = 0; i < grid.rows; i++) {
			for (size_t j = 0; j < grid.columns; j++) {

				//stocker les coordonnées actuelles
				const Coordinate coordinate = {i,j};

				//stocker les coordonnées de la k-ième direction
				const Coordinate neighbour = {i + directions[k].row,j + directions[k].col };

				if (!gridIsValidCoordinate(&grid, neighbour) ||
					gridIsEmptyBox(&grid, neighbour) ||
					gridIsEmptyBox(&grid, coordinate)) {
					continue;
					}

				// Vérifier si la grille contient une séquence viable
				gridSwapBoxes(&grid, neighbour, coordinate);
				const Sequence sequence = getLongestSequences(&grid);
				gridSwapBoxes(&grid, neighbour, coordinate);

				if (sequence.length != 0) {
					return false;
				}
			}
		}
	}
	return true;
}

size_t evaluateScore(const size_t X, const size_t N) {
	return (N + 1) * (X - 1) * (X - 1);
}
