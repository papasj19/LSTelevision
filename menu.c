
#include "menu.h"

void mainMenu(){

    printf("1. Login.\n");
    printf("2. Sign-up.\n");
    printf("3. Exit.\n");

}

void producerMenu(){

    printf("\n1.Clients | 2.Budget | 3.Channels | 4.Programs | 5.Actors | 6.Ads | 7.Movies | 8. Exit\n");

}

int clientManageMenu(){
        int input_choice = 0;
    int flag = 0;
    do{
        flag = 0;
        printf("1.Modify Client | 2.Delete Client");
        printf("\nEnter choice: ");
        scanf("%d", &input_choice);
        if(input_choice > 2 || input_choice < 1){
            printf("input undesirable\n");
            flag = 1;
        }
    }while(flag == 1);

        return input_choice;
}

int adMenu(){
        int input_choice = 0;
    int flag = 0;
    do{
        flag = 0;
        printf("1.Add ad | 2.Modify ad | 3.Remove ad | 4.Activate ad");
        printf("\nEnter choice: ");
        scanf("%d", &input_choice);
        if(input_choice > 4 || input_choice < 1){
            printf("input undesirable\n");
            flag = 1;
        }
    }while(flag == 1);
    return input_choice;
}

int channelMenu(){
        int input_choice = 0;
    int flag = 0;
    do{
    flag = 0;
        printf("1.New Channel | 2.Modify Channel | 3.Delete Channel");
        printf("\nEnter choice: ");
        scanf("%d", &input_choice);
        if(input_choice > 3 || input_choice < 1){
            printf("input undesirable\n");
            flag = 1;
        }
    }while(flag == 1);

        return input_choice;
}

int programMenu(){
        int input_choice = 0;
    int flag = 0;
    do{
    flag = 0;
        printf("1.Add Program to Channel | 2.Cancel Program");
        printf("\nEnter choice: ");
        scanf("%d", &input_choice);
        if(input_choice > 2 || input_choice < 1){
            printf("input undesirable\n");
            flag = 1;
        }
    }while(flag == 1);

        return input_choice;

}



int actorMenu(){
        int input_choice = 0;
    int flag = 0;
    do{
    flag = 0;
        printf("1.Register Actor | 2.Hire Actor For show | 3.Dismiss Actor");
        printf("\nEnter choice: ");
        scanf("%d", &input_choice);
        if(input_choice > 3 || input_choice < 1){
            printf("input undesirable\n");
            flag = 1;
        }
    }while(flag == 1);

        return input_choice;

}

void manageActorsMenu() {
    //Display the options
    printf("\nWhat do you want to do?\n");
    printf(" 1.Manage an Actor\n");
    printf(" 2.Add a new Actor\n");
    printf(" 3.Delete an Actor\n");
    printf(" 4.Display all Actors\n");
    printf(" 5.go to Main Menu\n");
}

void searchActorByMenu() {
    printf("Find the actor\n");
    printf("\t1.Search by ID.\n");
    printf("\t2.Search name + surname.\n");
    printf("\t3.Search by phone number.\n");
    printf("\t4.Abort.\n");
}

void doMenu(){
    int input_choice = 0;
    int menu_choice = 0;
    do{
        menu_choice = 0;
        switch(menu_choice){
                case 1:
                        input_choice = clientManageMenu();
                        break;
                case 2:
                        //budget
                        break;
                case 3:
                    input_choice = channelMenu();
                        break;
                case 4:
                    input_choice = programMenu();
                        break;
                case 5:
                    input_choice = actorMenu();
                    break;
                case 6:
                    input_choice = adMenu();
                        break;
            case 7:
                //movies():
                break;
        }
    }while(menu_choice != 8);
}


int addCardMenu(){
    int input_choice = 0;
    int flag = 0;
    do{
        flag = 0;
        input_choice = askForInteger("1.Credit Card | 2.Gift Card | 3.Exit\n> ");
        if(input_choice > 3 || input_choice < 1){
            printf("input undesirable\n");
            flag = 1;
        }
    }while(flag == 1);
    return input_choice;
}

int channelSubMenu(){
    int input_choice = 0;
    int flag = 0;
    do{
        flag = 0;
        input_choice = askForInteger("1.List | 2.Subscribe | 3.Cancel Sub | 4.List Programs on Channel | 5.Exit\n> ");
        if(input_choice > 5 || input_choice < 1){
            printf("input undesirable\n");
            flag = 1;
        }
    }while(flag == 1);
    return input_choice;
}

int programSubMenu(){
    int input_choice = 0;
    int flag = 0;
    do{
        flag = 0;
        input_choice = askForInteger("1.Filter | 2.Search | 3.View Planning | 4.Download Planning | 5.List Current | 6.Exit\n> ");
        if(input_choice > 6 || input_choice < 1){
            printf("input undesirable\n");
            flag = 1;
        }
    }while(flag == 1);
    return input_choice;
}




void clientMainMenu(Program** programs, int* progams_size, Channel** channels, int * channels_size){
    int input_choice = 0;
    do {
        input_choice = askForInteger("1.Card | 2.Movies | 3.Channels | 4.Programs | 5.Exit\n> ");
        int flag = 0;
        switch (input_choice) {
            //card menu
            case 1:
                do {
                    switch (addCardMenu()) {
                        case 1:
                            //add credit card
                            break;
                        case 2:
                            //add gift card
                            break;
                        case 3:
                            flag = 1;
                            break;
                    }
                }while(flag == 0);
                flag = 0;
                break;
            case 2:
                //movies
                break;
            case 3:
                do {
                    switch (channelSubMenu()) {
                        case 1:
                            //list channel
                            break;
                        case 2:
                            //subscribe to channel
                            break;
                        case 3:
                            //cancel sub
                            break;
                        case 4:
                            //list progs on channel
                            break;
                        case 5:
                            flag = 1;
                            break;
                    }
                }while(flag == 0);
                break;
            case 4:
                do {
                    switch (programSubMenu()) {
                        case 1:
                            searchByFilter(*programs,*progams_size);
                            break;
                        case 2:
                            //search
                            break;
                        case 3:
                            //View
                            break;
                        case 4:
                            //download
                            break;
                        case 5:
                            displayPrograms(*programs,*progams_size);
                            break;
                        case 6:
                            flag = 1;
                            break;
                    }
                }while(flag == 0);
                flag = 0;
                break;
        }
    }while(input_choice != 5);
}



void manageClientMenu() {
    printf("\n1.Modify a Client | 2.Delete a Client | 3.Display Clients | 4.Go Back\n");
}

void searchClientByMenu() {
    printf("Find the client by:\n");
    printf("\t1.Search by ID.\n");
    printf("\t2.Search by email.\n");
    printf("\t3.Abort.\n");
}
