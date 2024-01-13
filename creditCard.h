#ifndef CREDITCARD_H_
#define CREDITCARD_H_

#include <stdio.h>
#include <stdlib.h>
#include "format_checking.h"

#define MAXCHAR 25

typedef struct{
    int card_number;
    int pin;
    char user_mail[MAXCHAR];
} CreditCard;

/*
 A function that interacts with the user to recieve a new card structure
 it returns the new card structure with the info the user has submitted
 */
CreditCard recieveNewCard();

int getDigits(int to_be_checked);

void writeCardsToFile(CreditCard cards[], int cards_size);

CreditCard addNewCard(CreditCard* creditCards[],int *creditcards_size);

CreditCard* readAllCreditCard(int* creditcards_size);

#endif
