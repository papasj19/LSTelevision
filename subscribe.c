#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subscribe.h"
#include "user.h"
#include "channel.h"

#define MAX_CHAR 25

/************************
 * @Purpose: Let user subscribe to the current channel and save the transaction
 *           in the database
 * @Parameters: in - current_user: Information of the user that wants to subscribe
 *                 - current_channel: Channel to which the user wants to subscribe
 *
 * @Returns: ----
 * @Author: Ivan Fernandez
 *************************/
void subscribeToChannel(User current_user, Channel current_channel) {
    char pin[MAX_CHAR];     //Pin introduced by the user
    int correct;            //Correctness of the introduced pin

    //Loop that keeps asking for the credit card pin until the correct one is introduced
    do {
        printf("Introduce your card pin");
        scanf("%s", pin);

        correct = checkPin(pin, current_user);

    } while (correct == 0);

    saveSubscriptionDatabase(current_user, current_channel);

}

/************************
 * @Purpose: Check the correctness of the introduced pin and check if its valid
 * @Parameters: in - current_user: Information of the user that wants to subscribe
 *                 - pin: Introduced pin to check
 *
 * @Returns: correct - "boolean variable" that indicates if the pin is valid and correct
 * @Author: Ivan Fernandez
 *************************/
int checkPin(char* pin, User current_user) {
    int correct = 0;
    int flag = 0;
    int i;

    //Check the format of the pin (Exception getter)
    if (strlen(pin) != 4) {
        printf("\tThe pin must contain 4 digits.\n");
    } else {

        //Loop that checks that the pin is all numbers
        for (i=0; i<4; i++) {
            if (pin[i] < '0' || pin[i] > '9') {
                flag++;
            }
        }

        if (flag != 0) {
            printf("\tThe pin must be an integer.\n");

        } else {
        //If the pin is a valid integer, check if it matches with the credit card one
           // if (current_user.card.pin == atoi(pin)) {
                correct = 1;
           // }

        }

    }

    return correct;

}

/****************
 * @Purpose: Save the information of the subscription into the database
 * @Parameters: in - current_user: Information of the user that wants to subscribe
 *                 - current_channel: Channel to which the user wants to subscribe
 * @Returns: ----
 * @Author: Ivan Fernandez
 ***************/
void saveSubscriptionDatabase (User current_user,  Channel current_channel) {
    FILE *fp;                       //Pointer for passing through the subscription file database
    char file_email[MAX_CHAR];      //Stores the diverse emails found in the file database
    int num_subs;                   //Number of subscriptions of the user that wants to subscribe
    int aux = 0;                    //used for exiting a loop


    fp = fopen("subscriptionfile.txt", "a+");

    if (NULL == fp) {
        printf("Sorry, there was a problem during the subscription process, try again later.\n");
    } else {


        //Loop that searches for the user in the file, to check if its his/her first subscription
        fgets(file_email, MAX_CHAR, fp);
        while (!feof(fp) && aux == 0) {
            //If the user was already subscribe to something
            if (!strcmp(file_email, current_user.email)) {
                fscanf(fp, "%d", &num_subs);
                aux = 1;
            }

            fgets(file_email, MAX_CHAR, fp);
        }


        //~~NOT THE FIRST SUBSCRIPTION~~//

        //Add a new line to the database and shift all the others
        if (aux == 1) {
            //Get to the line where the subscriptions information of the user starts
            fseek(fp, -2, SEEK_CUR);

            //get email
            fgets(file_email, MAX_CHAR, fp);

            //Write the number of subscriptions
            fprintf(fp, "%d", (num_subs++));

            //Write the new channel subscription
            fseek(fp, num_subs, SEEK_CUR);
            //fprintf(current_channel.name, 1, sizeof(current_channel.name), fp);

        }


        //~~THE FIRST SUBSCRIPTION~~//

        /*Write at the end of the file the user email, the number of subscriptions, and the channel they are
        subscribed to in each of the subscriptions*/
        if (aux == 0) {
            fseek(fp, -1, SEEK_END);

            fwrite(current_user.email, 1, sizeof(current_user.email), fp);
            fprintf(fp, "1\n");
            fwrite(current_channel.name, 1, sizeof(current_channel.name), fp);

        }

        fclose(fp);

        printf("Congrats! You are now subscribed to %s.", current_channel.name);

    }


}
