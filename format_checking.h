//
// Created by Ivan Fernandez on 1/5/2024.
//

#ifndef FOR_STORIES_FORMAT_CHECKING_H
#define FOR_STORIES_FORMAT_CHECKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCHAR 25

int checkCharacter(char to_check[]);
int checkInteger(char str[]);
int askForInteger(char message[]);
void stringToLower(char str[]);
int uniquePhone(int phone, int phones[], int size);
int checkFloat(char str[]);
float askForFloat(char message[]);


#endif //FOR_STORIES_FORMAT_CHECKING_H
