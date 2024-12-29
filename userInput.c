//
// Created by Matis on 29/12/2024.
//

#include "userInput.h"

bool isUpperCaseLetter(const char letter) {
	return letter >= 'A' && letter <= 'Z';
}

bool isLowerCaseLetter(const char letter) {
	return letter >= 'a' && letter <= 'z';
}

bool isNumber(const char letter) {
	return letter >= '0' && letter <= '9';
}

ErrorCode strToCoord(const char in_coord[2], Coordinate *coordinate) {
	/**
	 * Objectif:
	 *		convertir une entrée utilisateur sous forme de coordonnées
	 *
	 *		Exemple:
	 *			A1, a1, 1A, 1a -> (0, 0)
	 *			B6, 6B, 6b, b6 -> (5, 1)
	 *
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 * A L G O R I T H M E
	 *
	 * Données d'entrées
	 *		coordonéesEntrée:		chaine de caractère de taille 2
	 *		coordonéesSortie:		structure (x, y)
	 *
	 * DEBUT
	 *		SI coordonéesEntrée[0] est une majuscule
	 *		ET coordonéesEntrée[1] est un lettre (maj ou min)
	 *
	 *			x <- conversionEntier(coordonéesEntrée[1]) - 1
	 *			y <- position de coordonéesEntrée[0] dans l'alphabet
	 *
	 *			coordonéesSortie <- (x, y)
	 *
	 *			renvoyer le code d'erreur SUCCESS
	 *		FIN SI
	 *
	 *		SI coordonéesEntrée[0] est un chiffre
	 *		ET coordonéesEntrée[1] est une lettre (maj ou min)
	 *
	 *			x <- position de coordonéesEntrée[0] dans l'alphabet
	 *			y <- conversionEntier(coordonéesEntrée[1]) - 1
	 *
	 *			coordonéesSortie <- (x, y)
	 *
	 *			renvoyer le code d'erreur SUCCESS
	 *		FIN SI
	 *
	 *		renvoyer le code d'erreur GENERIC_ERROR
	 * FIN
	 */
	const bool isAlphaNum = isUpperCaseLetter(in_coord[0]) && isNumber(in_coord[1]);
	const bool isNumAlpha = isUpperCaseLetter(in_coord[1]) && isNumber(in_coord[0]);
	const bool is_alphaNum = isLowerCaseLetter(in_coord[0]) && isNumber(in_coord[1]);
	const bool isNum_alpha = isLowerCaseLetter(in_coord[1]) && isNumber(in_coord[0]);

	if (isAlphaNum) {
		coordinate->row = in_coord[1] - '0' - 1;
		coordinate->col = in_coord[0] - 'A';
		return SUCCESS;
	}

	if (isNumAlpha) {
		coordinate->row = in_coord[0] - '0' - 1;
		coordinate->col = in_coord[1] - 'A';
		return SUCCESS;
	}

	if (is_alphaNum) {
		coordinate->row = in_coord[1] - '0' - 1;
		coordinate->col = in_coord[0] - 'a';
		return SUCCESS;
	}

	if (isNum_alpha) {
		coordinate->row = in_coord[0] - '0' - 1;
		coordinate->col = in_coord[1] - 'a';
		return SUCCESS;
	}

	return GENERIC_ERROR;
}