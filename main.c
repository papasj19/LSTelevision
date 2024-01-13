//#include "channel.h"
#include "user.h"
//#include "budget.h"
#include "actor.h"
#include "menu.h"
#include "client.h"

void modeMenu();
void loginMenu();
int checkMenuOption(char str[]);
void runProducer(User** users, int *users_size, User* current_user, Actor** actors, int *actors_size);
void runClient(User** users, User* current_user);


int main(void){
    User* users;                                    // All users using the program
    Actor* actors;                                  // All actors in the system
    User current_user;                              // user using the program
    int action;
    int exit = 0;
    int go_back = 0;
    int mode;
    int valid = 0;                                  // 'Boolean' value used for checking credentials
    char menu_option[MAXCHAR];
    char tmp[MAXCHAR];
    int users_size;
    int actors_size;


    users = readAllUsers(&users_size);
    actors = readAllActors(&actors_size);

    for (int i=0; i<users_size; i++) {

        printf("\n(%s) %s [%s]\n", users[i].id, users[i].name, users[i].email);
    }


    mainMenu();

    //Receive user input and check if its valid
    printf("\nAccess: ");
    do{
        scanf("%s", menu_option);
        if (!checkMenuOption(menu_option)) {
            printf("\nIncorrect Option, try again: ");
        }
    } while (!checkMenuOption(menu_option));

    // Allows user to change between sign-up login more effectively and smoothly
    do {

        // reset go back
        go_back = 0;

        //Depending on the user input,
        switch (menu_option[0]) {
                // Login
            case '1':
                do {
                    loginMenu();
                    action = askForInteger("\nSelect an option: ");
                    if (action == 1) {
                        current_user = loginUser(users, users_size, &valid);
                    }

                    if (action == 2) {
                        go_back = 1;
                        menu_option[0] = '2';
                    }

                    if (action == 3) {
                        exit = 1;
                    }

                } while (!valid && !go_back && !exit);
                printf("TYPE: %d", current_user.type);
                break;

                // Sign-up
            case '2':

                do {
                    modeMenu();

                    // Ask for the type of user, or if user wants to retrieve
                    action = askForInteger("\nSelect an option: ");
                    do {
                        if (action > 4 || action < 1) {
                            action = askForInteger("\nSelect a valid option: ");
                        }
                    } while (action > 4 || action < 1);

                    // Create a producer or client account depending on the selected option
                    if (action == 1 || action == 2) {
                        printf("\n\nCHEK 1\n\n");
                        current_user = registerNewUser(&valid, action - 1);
                        if (!valid) {
                            printf("\nIncorrect format! Make sure of your credentials and try again.\n\n");
                        }
                        printf("\n\nCHECK 2\n\n");
                        users_size++;
                        users = realloc(users, (users_size * sizeof(User)));
                        users[users_size - 1] = current_user;
                    }

                    // If user already has an account, redirect to log in process
                    if (action == 3) {
                        go_back = 1;
                        menu_option[0] = '1';
                    }

                    if (action == 4) {
                        exit = 1;
                    }

                } while (!valid && !go_back);

                break;

                // Exit
            case '3':
                printf("\nThanks for using LST_Manager, hope to see you soon!\n\n");
                exit = 1;
                break;
        }

    } while (go_back);




    if (!exit) {
        if (current_user.type == PRODUCER) {
            runProducer(&users, &users_size, &current_user, &actors, &actors_size);
        } else {
            runClient(&users, &current_user);
        }
    }


    updateDatabaseUser(&users, &users_size);
    updateDatabaseActors(&actors, &actors_size);
    free(users);
    free(actors);

    return 0;
}



void modeMenu() {
    printf("\nWhat do you desire to do?\n");
    printf("\t1) Producer Mode.\n");
    printf("\t2) Client Mode.\n");
    printf("\t3) I already have an account.\n\n");
    printf("\t4) Exit.\n");
}

void loginMenu() {
    printf("\nWhat do you desire to do?\n");
    printf("\t1) Proceed.\n");
    printf("\t2) Create a new Account.\n\n");
    printf("\t3) Exit.");
}

/***********
* @Purpose: Check if the user input is a valid option
* @Parameters: in: str - user input to check
* @Returns: boolean explaining if the input is valid (1) or not (0)
***********/
int checkMenuOption(char str[]) {

    //If the input is a character check if it is a valid one
    if (checkInteger(str)) {
        if (strlen(str) == 1) {
            if (atoi(str) > 0 && atoi(str) < 4) {
                return 1;
            }
        }

    }

    return 0;
}

void runProducer(User* users[], int *users_size, User* current_user, Actor* actors[], int *actors_size) {
    int exit = 0;
    int action;


    do {

        producerMenu();
        action = askForInteger("Select an option: ");

        switch (action) {
            case 1:
                manageClients(users, users_size);
                break;
            case 2:
                //budget
                break;
            case 3:
                // input_choice = channelMenu();
                break;
            case 4:
                //  input_choice = programMenu();
                break;
            case 5:
                actorsOptions(actors, actors_size);
                break;
            case 6:
                // input_choice = adMenu();
                break;
            case 7:
                //movies():
                break;
            case 8:
                exit = 1;
                break;
        }

    } while (!exit);


}

void runClient(User** users, User* current_user) {
    printf("\nClient.\n");

}

