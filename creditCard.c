#include "creditCard.h"


/*
 A function that interacts with the user to recieve a new card structure
 it returns the new card structure with the info the user has submitted
 */
CreditCard recieveNewCard(){
    CreditCard new_info;
    printf("\nPlease enter the user's email associated with the card: ");
    scanf("%s",new_info.user_mail);
    do{     //loop utilized to check correctness of user input
        int temp = askForInteger("Please enter the card number: ");
        if(getDigits(temp) != 10){
            printf("You have entered the incorrect number of digits for the card");
        }else{
            new_info.card_number = temp;
        }
    }while(getDigits(new_info.card_number) != 10);
    do{
        int temppin = askForInteger("Please enter the PIN: ");
        if(getDigits(temppin) != 4){
            printf("You have entered the incorrect number of digits for the pin of the card");
        }else{
            new_info.pin = temppin;
        }
    }while(getDigits(new_info.pin) != 4);
    return new_info;
}


/*
 used to calculate the number of digits in an integer
 */
int getDigits(int to_be_checked){
    int count = 0;
    while(to_be_checked>1){
        count++;
        to_be_checked = to_be_checked/10;
    }
    return count;
}




void writeCardsToFile(CreditCard cards[], int cards_size){
    FILE * the_file;
    the_file = fopen("creditcardfile.txt", "a");
    if(the_file != NULL) {

        fprintf(the_file, "%d\n\n", cards_size);
        for(int i = 0; i<cards_size; i++) {
            fprintf(the_file, "%d", cards[i].card_number);
            fprintf(the_file, "\n");
            fprintf(the_file, "%d", cards[i].pin);
            fprintf(the_file, "\n");
            fprintf(the_file, "%s", cards[i].user_mail);
            fprintf(the_file, "\n\n");
        }
        fclose(the_file);
    }
}


/*
 A function that checks the users email with the existing emails in the system and reports the result
 
 We need to check in the user functions for null to safeguard our system
 */
CreditCard addNewCard(CreditCard* creditCards[],int *creditcards_size){
    CreditCard temp = recieveNewCard();
    creditCards = realloc(creditCards, (((*creditcards_size)+1) * sizeof(CreditCard)));
    (*creditcards_size)++;
    (*creditCards)[*creditcards_size-1] = temp;
    return temp;
}

CreditCard* readAllCreditCard(int* creditcards_size){
    CreditCard* creditCards;
    FILE *fp;
    int i;
    char trash;
    int temp_size;

    creditCards = malloc(sizeof(CreditCard));
    (*creditcards_size) = 0;

    fp = fopen("creditcards.txt", "r");
    if (fp == NULL){
        printf("Error opening the file.\n");
    }else{
        fscanf(fp, "%d", &temp_size);
        fscanf(fp, "%c", &trash);

        (*creditcards_size) = temp_size;
        creditCards = realloc(creditCards, ((*creditcards_size) * sizeof(CreditCard)));

        for (i = 0; i < *creditcards_size; i++) {
            fscanf(fp,"%d", &creditCards[i].card_number);
            fscanf(fp, "%c", &trash);

            fscanf(fp, "%d", &creditCards[i].pin);
            fscanf(fp, "%c", &trash);

            fscanf(fp,"%s", creditCards[i].user_mail);
            fscanf(fp, "%c", &trash);
        }
        fclose(fp);
    }
    return creditCards;
}


