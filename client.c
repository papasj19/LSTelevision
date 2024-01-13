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
                manageClient(users, users_size, DELETE);
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

    do {
        searchClientByMenu();
        option = askForInteger("Select an option: ");

        switch (option) {
            // Search By ID
            case 1:

                num_id = askForInteger("Introduce the id (number only): ");
                itoa(num_id, id, 10);

                strcpy(tmp, "C");
                strcat(tmp, id);

                for (i = 0; i < *users_size; i++) {
                    char to_check[MAXCHAR];

                    printf("CHECK1\n");
                    strcpy(to_check, users[i]->id);
                    printf("CHECK2\n");

                    if (!strcmp(to_check, tmp)) {
                        pos = i;
                    }

                }

                strcpy(id, "\0");

                printf("\n\nID: %s\n", id);

                break;

                // Search By email
            case 2:

                printf("Introduce the email: ");
                scanf("%s", email);

                for (i = 0; i < (*users_size); i++) {
                    char to_check[MAXCHAR];

                    strcpy(to_check, users[i]->email);

                    if (!strcmp(email, to_check)) {
                        pos = i;
                    }
                }
                if (users[pos]->type == PRODUCER) {
                    printf("\n(ERROR) Not possible to access a Producer Account!\n\n");
                    pos = -2;
                }

                break;

                // Exit
            case 3:
                printf("\nAborting... Going back...\n\n");
                pos = -2;
                break;

            default:
                printf("Incorrect input, select a valid option (1, 2, 3).\n");
                break;

        }


        if (mode == MODIFY) {

            changeUser(users, users_size, pos);


        }
        if (mode == DELETE) {
            char confirm;

            printf("Deleting:\n");
            printf("\n>User(%s) %s [%s]\n", users[pos]->id, users[pos]->name, users[pos]->email);
            confirm = askForSure("Are you sure? (Y/N): ");

            switch (confirm) {
                case 'Y':
                    printf("\nDeleting -->User(%s) %s [%s]...\n", users[pos]->id, users[pos]->name, users[pos]->email);

                    // shift all users
                    for (i = pos; i < (*users_size) - 1; i++) {
                        users[i] = users[i + 1];
                    }

                    // Readjust Arrays
                    (*users_size)--;
                    users = realloc(users, (*users_size * sizeof(User)));

                    printf("User successfully deleted.\n");

                    break;

                case 'N':
                    printf("Aborting process...\n");

            }

        }

    } while (pos != -2);


} // Manage Client


void changeUser(User *users[], int *users_size, int pos) {
    int option;
    String name;
    String id;
    int num_id;
    String email;
    String password;
    String tmp;

    modifyUserMenu();
    askForInteger("Select an Option: ");

    switch (option) {

        // Modify ID
        case 1:

            num_id = askForInteger("Introduce new user's id (numbers only): ");
            itoa(num_id, id, 10);

            strcpy(tmp, "C");
            strcat(tmp, id);
            strcpy(id, tmp);

            printf("\n\nID: %s\n", id);

            strcpy(users[pos]->id, id);

            break;

        // Modify Name
        case 2:

            printf("Introduce the new user's name: ");
            scanf("%s", name);

            strcpy(users[pos]->name, name);

            break;

        // Modify Email
        case 3:

            printf("Introduce the new user's email: ");
            scanf("%s", email);

            if (checkEmail(email)) {
                strcpy(users[pos]->email, email);
            } else {
                printf("incorrect email format!\n");
            }

            break;

        // Modify Password
        case 4:

            printf("Introduce the new user's name: ");
            scanf("%s", password);

            strcpy(users[pos]->password, password);

            break;


        default:
            printf("Introduce a valid option (1, 2, 3, 4, 5).\n\n");
            break;

    }

}