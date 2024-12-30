//
// Created by Matis on 30/12/2024.
//

#ifndef SCORE_H
#define SCORE_H
#include <stddef.h>

#include "dataType.h"

int userExist(const char* username);
void setUserScore(const UserScore usr_score);
UserScore* getUserScore();
int newUsernameIndex();
void writeScore();
void readUserScore();
#endif //SCORE_H
