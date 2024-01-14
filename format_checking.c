//
// Created by Ivan Fernandez on 1/5/2024.
//

#include "format_checking.h"


/******************************************************************************
 * @Purpose: Execute all the process of asking the user for an integer,
 *           handling the format exceptions
 * @Parameters: in: message = To print in the console for asking the user
 * @Returns: the correct and valid integer introduced by the user
 * @Authors: Ivan Fernandez
 ******************************************************************************/
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



/******************************************************************************
 * @Purpose: Execute all the process of asking the user for a float,
 *           handling the format exceptions
 * @Parameters: in: message = To print in the console for asking the user
 * @Returns: the correct and valid float introduced by the user
 * @Authors: Spencer
 ******************************************************************************/
float askForFloat(char message[]) {
    char input[MAXCHAR];

    printf("%s", message);
    do {
        scanf("%s", input);

        if (!checkFloat(input)) {
            printf("\nPlease, input a valid format: ");
        }
    } while (!checkFloat(input));

    return atof(input);

}


/******************************************************************************
 * @Purpose: Global function to check if an input is a character
 * @Parameters: in - str: string to check correctness
 * @Returns: "boolean" explaining if the given string is a character [0-no,1-yes]
 * @Authors: Ivan Fernandez
 ******************************************************************************/
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



/*********************************************************************************
 * @Purpose: Global function to check if an input is an integer
 * @Parameters: in - str: string to check correctness
 * @Returns: "boolean" explaining if the given string is an integer [0-no,1-yes]
 * @Authors: Ivan Fernandez
 ********************************************************************************/
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


/*********************************************************************************
 * @Purpose: Global function to check if an input is a float
 * @Parameters: in: str = user input to check format
 * @Returns: "boolean" explaining if the given string is a float [0-no,1-yes]
 * @Authors: Spencer
 ********************************************************************************/
int checkFloat(char str[]) {
    int i = 0, flag = 0;
    int saver = 0;

    //Check for a non-number-character in the string
    for (i=0; i<strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            if(str[i] == '.'){
                i = saver;
                break;
            }else {
                flag++;
            }
        }
    }
    saver++;
    //Check for a non-number-character in the string
    for (i=saver; i<strlen(str); i++) {
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



/******************************************************************************
 * @Purpose: transforms the given string to lowercase
 * @Parameters: in: str = string to pass to lowercase
 * @Returns: ----
 * @Authors: Ivan Fernandez
 ******************************************************************************/
void stringToLower(char str[]) {
    int i;
    char to_return[strlen(str)];

    for (i=0; i< strlen(str); i++) {
        str[i] = tolower(str[i]);
    }

}


/******************************************************************************
 * @Purpose: Check if the introduced phone number is in use by other actors
 * @Parameters: in: phone = phone to be added, to check if not repeated
 *              in: phones = existing phones in the system, in use
 *              in: size = number of phones in the system
 * @Returns: boolean indicating if phone is unique
 * @Authors: Ivan Fernandez
 ******************************************************************************/
int uniquePhone(int phone, int phones[], int size) {

    for (int i=0; i<size; i++) {
        if (phone == phones[i]) {
            return 0;
        }
    }

    return 1;

}
