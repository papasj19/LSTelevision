//
// Created by Ivan Fernandez on 1/5/2024.
//

#include "format_checking.h"



int askForInteger(char message[]) {
    char input[MAXCHAR];

    printf("%s", message);
    do {
        scanf("%s", input);

        if (!checkInteger(input)) {
            printf("\nPlease, input a valid format: ");
        }
    } while (!checkInteger(input));

    return atoi(input);

}

/***********
 * @Purpose: Global function to check if an input is a character
 * @Parameters: in - str: string to check correctness
 * @Returns: "boolean" explaining if the given string is a character [0-no,1-yes]
 * @Authors: Ivan Fernandez
 */
int checkCharacter(char to_check[]) {
    if (strlen(to_check) > 1) {
        return 0;
    } else {
        if (toupper(to_check[0]) < 'A' || toupper(to_check[0]) > 'Z') {
            return 0;
        }
    }

    return 1;
}



/***********
 * @Purpose: Global function to check if an input is an integer
 * @Parameters: in - str: string to check correctness
 * @Returns: "boolean" explaining if the given string is an integer [0-no,1-yes]
 * @Authors: Ivan Fernandez
 */
int checkInteger(char str[]) {
    int i = 0, flag = 0;

    //Check for a non-number-character in the string
    for (i=0; i<strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            flag++;
        }
    }

    //If all numbers, then integer
    if (flag == 0) {
        return 1;
    }

    return 0;


}


void stringToLower(char str[]) {
    int i;
    char to_return[strlen(str)];

    for (i=0; i< strlen(str); i++) {
        str[i] = tolower(str[i]);
    }

}


int uniquePhone(int phone, int phones[], int size) {

    for (int i=0; i<size; i++) {
        if (phone == phones[i]) {
            return 0;
        }
    }

    return 1;

}
