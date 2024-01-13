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
            // Modify client
            case 1:
                manageClient(users, users_size, MODIFY);
                break;

            // Delete Client
            case 2:

                break;

            // Display Clients
            case 3:


                displayClients(*users, *users_size);

                break;

            case 4:
                exit = 1;
                break;

            default:
                printf("Invalid option, select a valid one (1, 2, 3, 4).\n");
        }



    } while (!exit);

} // End of Manage Client



void displayClients(User users[], int size) {
    int i;

    for (i=0; i<size; i++) {
        if (users[i].type == CLIENT) {
            printf("\n>User(%s) %s [%s]\n", users[i].id, users[i].name, users[i].email);
        }
    }
}


void manageClient(User *users[], int *users_size, int mode) {
    int pos = -1;
    int i;
    int option;
    char id[MAXCHAR];
    int num_id;
    char email[MAXCHAR];
    char tmp[MAXCHAR];

    searchClientByMenu();
    option = askForInteger("Select an option: ");

    switch (option) {
        // Search By ID
        case 1:

            num_id = askForInteger("Introduce the id (number only): ");
            itoa(num_id, id, 10);

            strcpy(tmp, "C");
            strcat(tmp, id);
            strcpy(id, tmp);

            printf("\n\nID: %s\n", id);

            for (i=0; i<(*users_size); i++) {
                char to_check[MAXCHAR];

                strcpy(to_check, users[i]->id);

                if (!strcmp(to_check, id)) {
                    pos = i;
                }
            }


            break;

        // Search By email
        case 2:
            break;

        default:
            printf("Incorrect input, select a valid option (1, 2, 3).\n");
            break;

    }


}