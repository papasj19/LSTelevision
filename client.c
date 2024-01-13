//
// Created by ivanf_uunngm1 on 1/13/2024.
//

#include "client.h"


/*******************
 * @Purpose: Allow the modification and deletion of clients to producers
 * @Parameters: in - users: array with all users
 *                 - users_size: number of users
 * @Return: ----
 * @Author: Ivan Fernandez
 *******************/
void manageClients(User *users[], int *users_size) {
    int option;
    int exit = 0;
    int i, j;


    do {

        manageClientMenu();
        option = askForInteger("Select an option: ");

        switch (option) {
            case 1:



                break;

            case 2:

                break;

            case 3:

                for (i=0; i<(*users_size); i++) {
                    if (users[i]->type == CLIENT) {
                        printf("\n(%s) %s [%s]\n", users[i]->id, users[i]->name, users[i]->email);
                    }
                }

                break;

            case 4:
                exit = 1;
                break;

            default:
                printf("Invalid option, select a valid one (1, 2, 3, 4).\n");
        }



    } while (!exit);




}