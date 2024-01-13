
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




void clientMainMenu(){

        printf("1.Card | 2.Movies | 3.Channels | 4 Programs");
}


void manageClientMenu() {
    printf("\n1.Modify a Client | 2.Delete a Client | 3.Display Clients | 4.Go Back\n");
}

void searchClientBy() {
    printf("a");
}
