//
// Created by Matis on 29/12/2024.
//

#ifndef USERINPUT_H
#define USERINPUT_H

#include "dataType.h"

/**
 * NB: 'isUpperCaseLetter', 'isLowerCaseLetter', 'isNumber'
 * sont de très petites fonctions, on les déclare dans le .h
 * avec le préfixe 'inline' pour ne pas avoir à les définir dans le .c
 * inline permet d'optimiser ces fonctions, au lieu qu'elles soient
 * appelée sur la pile le compilateur les remplacera par leur expression booléenne
 */

/**
 * @brief Déterminer si un caractère est une lettre est majuscule
 * @param letter
 * @return bool — true si le caractère est une lettre majuscule sinon false
 */
bool isUpperCaseLetter(const char letter);
/**
 * @brief Déterminer si un caractère est une lettre est minuscule
 * @param letter
 * @return bool — true si le caractère est une lettre minuscule sinon false
 */
bool isLowerCaseLetter(const char letter);

/**
 * @brief Déterminer si un caractère est un chiffre
 * @param letter
 * @return bool — true si le caractère est un chiffre sinon false
 */
bool isNumber(const char letter);

ErrorCode strToCoord(const char in_coord[2], Coordinate *coordinate);

#endif //USERINPUT_H
