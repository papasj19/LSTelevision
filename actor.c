#include "actor.h"
#include "menu.h"

/**************
 * @Purpose: Get the actors from the database
 * @Parameters: in - actors_size: pointer to the number of actors in the
 *                                to be changed in this function
 * @Returns: All actors from the database
 * @Author Ivan Fernandez
 ****************/
Actor* readAllActors(int *actors_size) {
    FILE *fp;
    Actor* actors;
    char tmp[MAXCHAR];
	char aux;


	actors = (Actor *) malloc(sizeof(Actor));
	(*actors_size) = 1;

    fp = fopen("actorfile.txt", "r");

    if (fp != NULL) {

        // Get id
        fscanf(fp, "%s", tmp);
        fscanf(fp, "%c", &aux);
        while (!feof(fp)) {
            //Set id after checking feof
            actors[*actors_size-1].id = atoi(tmp);

            //Get Name
            fgets(tmp, MAXCHAR, fp);
            tmp[strlen(tmp)-1] = '\0';
            strcpy(actors[*actors_size-1].name, tmp);

            //Get Surname
            fgets(tmp, MAXCHAR, fp);
            tmp[strlen(tmp)-1] = '\0';
            strcpy(actors[*actors_size-1].surname, tmp);

            //Get Phone Number
            fscanf(fp, "%s", tmp);
            fscanf(fp, "%c", &aux);
            actors[*actors_size-1].phone = atoi(tmp);

            //Get Salary
            fscanf(fp, "%s", tmp);
            fscanf(fp, "%c", &aux);
            actors[*actors_size-1].salary = atoi(tmp);

            //Program reading not discussed yet the final format

            (*actors_size)++;
            actors = realloc(actors, (*actors_size * sizeof(Actor)));

            //Check for feof
            fscanf(fp, "%c", &aux);
            fscanf(fp, "%s", tmp);
            fscanf(fp, "%c", &aux);

        }

        (*actors_size)--;

        return actors;
    }

    return NULL;
} //End of readAllActors()

/*************
* @Purpose: Save all the actors and the changes done to the database
* @Parameters: in: actors - array of Actor with all the actors
*                  user_size - pointer to the number of actors in the database
* @Returns: ----
* @Author: Ivan Fernandez
**************/
void updateDatabaseActors(Actor *actors[], int *actors_size) {
    FILE *fp;
    int i;

    fp = fopen("actorfile.txt", "w");
    if (fp != NULL) {

        for (i=0; i<(*actors_size); i++) {
            fprintf(fp, "%d\n%s\n%s\n%d\n%d\n\n", actors[i]->id, actors[i]->name, actors[i]->surname, actors[i]->phone, actors[i]->salary);
        }

    }

} //End of updateDatabaseActors


//checks the number of digits for the phone number
int checkDigits(int to_check){
        int count = 0;
        while(to_check>0){
                count++;
                to_check = to_check/10;
        }
    return count;
}

//counts the number of actors in the file
int checkNumActors(){
    FILE * the_file;
    Actor temp;
    char trash;
    int count = 0;
    the_file = fopen("actorfile.txt", "r");
    if(the_file != NULL){
            fscanf(the_file, "%d", &temp.id);
            while(!feof(the_file)){
                count++;
                fscanf(the_file, "%c", &trash);
                fscanf(the_file, "%s", temp.name);
                fscanf(the_file, "%s", temp.surname);
                fscanf(the_file, "%d", &temp.phone);
                fscanf(the_file, "%c", &trash);
                fscanf(the_file, "%d", &temp.salary);
                fscanf(the_file, "%c", &trash);
                fscanf(the_file, "%c", &trash);
                fscanf(the_file, "%d", &temp.id);
            }
        fclose(the_file);
            return count;
    }else{
            return 0;
    }

}


//utilizes console to receive information about an actor from the user
Actor addNewActor(Actor actors[], int actors_size){
        Actor temp;                     // Actor to create
        int numbers[actors_size];       // Phone numbers of all actors
        int unique = 0;                 // Boolean describing if the new actor's phone number is unique
        int last_id = 0;

        printf("Enter the name: ");
        scanf("%s", temp.name);
        printf("Enter the surname: ");
        scanf("%s", temp.surname);

        // Keep asking for the phone number until a valid and unique one is inputted
        do{
            temp.phone = askForInteger("Enter the phone (9-digits): ");

            if(checkDigits(temp.phone) != 9){
                printf("The phone number has the wrong number of digits, please try again\n");
            }

            for (int i=0; i<actors_size; i++) {
                numbers[i] = actors[i].phone;
            }
            unique = uniquePhone(temp.phone, numbers, actors_size);
            if (!unique) {
                printf("This phone number is already in use, check your input and try again.\n");
            }


        }while(checkDigits(temp.phone) != 9 || !unique);

        // Add salary
        temp.salary = askForInteger("Enter the salary: ");

        // Generate the ID
        if (actors_size > 0) {
            last_id = actors[actors_size - 1].id + 1;
        }
        temp.id = last_id;
        printf("\n\nsize: %d\n\n", actors[0].id);

        return temp;
}



//opens and closes the file as well as writing the information of a new actor to the file
int addNewActorToFile(Actor to_be_written){
        FILE * the_file;
        the_file = fopen("actorfile.txt", "a");
        if(the_file != NULL){
                fprintf(the_file, "%d", checkNumActors()+1);
                fprintf(the_file, "\n");
                fprintf(the_file, "%s", to_be_written.name);
                fprintf(the_file, "\n");
                fprintf(the_file, "%s", to_be_written.surname);
                fprintf(the_file, "\n");
                fprintf(the_file, "%d", to_be_written.phone);
                fprintf(the_file, "\n");
                fprintf(the_file, "%d", to_be_written.salary);
                fprintf(the_file, "\n\n");
                fclose(the_file);
                return 1;
        }else{
                return 0;
        }
}





/**************
 * @Purpose: Display the actors who are not in any program
 * @Parameters: in - actors: array with all actors
 * @Returns: ----
 * @Author Ivan Fernandez
 ****************/
void displayUnemployedActors(Actor actors[], int *actors_size) {
    int i = 0;

    for (i=0; i<(*actors_size); i++) {

        if (strcmp(actors[i].program,"")==0) {
            printf("Actor: %d\n", actors[i].id);
            printf("\t%s %s", actors[i].name, actors[i].surname);
            printf("\tcontact: %d, %dEuros", actors[i].phone, actors[i].salary);
        }

    }

}

/**************
 * @Purpose: Given an ID introduced by the user, find the actor with that id in the database
 * @Parameters: in - actors: array with all actors
 * @Returns: position in the array of the selected actor
 * @Author Ivan Fernandez
 **************/
int getActorFromUser(Actor *actors[], int *actors_size) {
    Actor trash;
    char tmp_id[MAXCHAR];
    int position;
    int i = 0, flag = 0;

    //Ask for an ID until a valid ID, meaning, an integer, is introduced
    printf("\nIntroduce the actor's ID: ");
    do {
        fgets(tmp_id, MAXCHAR, stdin);

        while (tmp_id[i] != '\n') {
            if (tmp_id[i] < '0' || tmp_id[i] > '9') {
                flag++;
            }
            i++;
        }
        if (flag != 0) {
            printf("\nIntroduce a valid ID: ");
        }
    } while (flag != 0);

    //Reset vars to use them again
    flag = 0;
    i = 0;

    //Search in the actor database the actor with matching IDs
    for (i=0; i<(*actors_size) && !flag; i++) {
        if (atoi(tmp_id) == actors[i]->id) {
            position = i;
            flag++;
        }
    }
    //If there is no actor with the introduced ID, display error message and return an ERROR
    if (flag == 0) {
        printf("\nThere is no Actor with '%d' ID", atoi(tmp_id));
        return (-1);
    }

    //Return position of actor with Matching ID
    return position;

}


/***********
 * @Purpose: Add the current program to the actor to hire
 * @Parameters: in - actors: array with all actors
 *                 - program: program from where the function has been called
 *                 - pos: position of tge actor to hire in the actors array
 * @Returns: ----
 * @Author Ivan Fernandez
 ************/
void hireActor(Actor *actors[], char program[], int pos) {

    if (pos != -1) {
        strcpy(actors[pos]->program, program);
        printf("\n%s %s (%d) is now in %s\n", actors[pos]->name,
               actors[pos]->surname, actors[pos]->id, program);
    } else {
        printf("(ERROR). Hire actor aborted... No actor hired\n");
    }

}

/************
 * @Purpose: Display and manage the different options for managing actors
 * @Parameters: in - actors: array with all actors
 * @Returns: ----
 * @Author: Ivan Fernandez
 ************/
void actorsOptions(Actor *actors[], int *actors_size) {
    char unt_option[MAXCHAR];   //Untreated option, option given by the user to check correctness
    char option;                //Valid input for option, no format error
    int invalid;                //Indicates if the input is invalid
    int mode;                   //Indicates the type of Actor management, to avoid having 2 almost identical functions
    int exit = 0;               //Indicates if the user wants to go back to the main menu

    //Keep the menu until user wants to go back
    do{

        manageActorsMenu();

        option = askForInteger("\nSelect an option: ") + '0';

        //Manage the different options && error case
        switch (option) {
            case '1':
                mode = 1;
                manageActors(actors, mode, actors_size);
                break;

            case '2':
                (*actors_size)++;
                actors = realloc(actors, (*actors_size * sizeof(Actor)));
                (*actors)[(*actors_size)-1] = addNewActor((*actors), (*actors_size)-1);
                break;

            case '3':
                mode = 2;
                manageActors(actors, mode, actors_size);
                break;

            case '4':
                displayActors(*actors, actors_size);
                break;

            case '5':
                printf("Aborting 'Manage actors'... Going Back...\n");
                exit = 1;
                break;

            default:
                printf("Select a valid option (1, 2, 3, 4, 5)");


        }
    } while (exit == 0);

}

/*******************
 * @Purpose: Display and manage the actors according to user input
 * @Parameters: in - actors: array with all actors
 *                 - mode: explains if the user wants to change or delete an actor
 * @Return: ----
 * @Author: Ivan Fernandez
 *******************/
void manageActors(Actor *actors[], int mode, int *actors_size) {
    char unt_option[MAXCHAR];
    char confirmation[MAXCHAR];
    int pos = -1;
    char tmp[MAXCHAR];
    int id;
    char name[MAXCHAR];
    char surname[MAXCHAR];
    int phone;
    char token[MAXCHAR];
    int i;
    int correct = 0;            //Bool to check input correctness
    int exit = 0;


    searchActorByMenu();

    unt_option[0] = askForInteger("Select an option: ") + '0';

    switch (unt_option[0]) {
        case '1':

            id = askForInteger("\nIntroduce the actor's ID: ");

            for (i=0; i<(*actors_size); i++) {
                int to_check = actors[i]->id;

                if (to_check == id) {
                    pos = i;
                }
            }
            i = 0;

            break;

        case '2':
            printf("\nIntroduce the actor's name: ");
            scanf("%s", name);
            printf("\nIntroduce the actor's surname: ");
            scanf("%s", surname);

            // Do search ignoring case, to prevent user error
            stringToLower(name);
            stringToLower(surname);


            for (i=0; i<(*actors_size); i++) {
                char aux_name[MAXCHAR];
                char aux_sur[MAXCHAR];

                // Do search ignoring case, to prevent user error
                strcpy(aux_name, actors[i]->name);
                strcpy(aux_sur, actors[i]->surname);

                stringToLower(aux_name);
                stringToLower(aux_sur);

                if (!strcmp(name, aux_name) && !strcmp(surname, aux_sur)) {
                    pos = i;
                }
            }
            i = 0;

            strcpy(token, name);

            break;

        case '3':

            phone = askForInteger("\nIntroduce the actor's phone number: ");

            for (i=0; i<(*actors_size); i++) {
                int to_check = actors[i]->phone;

                if (phone == to_check) {
                    pos = i;
                }
            }

            //itoa(phone, token, 10);
            snprintf(token,10,"%d",phone);

            break;

        case '4':
            exit = 1;
            pos = -2;
			return;
            break;

        default:
            printf("\nInput a valid option (1, 2, 3, 4)");
            pos = -2;
            break;

    }

    // Modify Actor
    if (mode == 1 && pos > -1) {

        changeActor(actors, pos);

    }
    // Delete Actor
    else {
		if (pos > -1) {
        if (mode == 2) {
            printf("Are you sure you want to delete:\n");
            printf("\tActor (%d), %s %s, %d", actors[pos]->id, actors[pos]->name,
                   actors[pos]->surname, actors[pos]->phone);

            printf("(Y/N):");
            do {
                scanf("%s", confirmation);

                if (strlen(confirmation) > 1) {
                    printf("\nintroduce a valid option (Y/N): ");
                } else {
                    if (toupper(confirmation[0]) != 'Y' && toupper(confirmation[0]) != 'N') {
                        printf("\nintroduce a valid option (Y/N): ");
                    } else {
                        correct = 1;
                    }
                }
            } while (!correct);

            switch (toupper(confirmation[0])) {
                case 'Y':
                    printf("Actor: %s, %s (%d)", actors[pos]->name, actors[pos]->surname, actors[pos]->phone);

                    //Shift all actors
                    for (i=pos; i<(*actors_size)-1; i++) {
                        actors[i] = actors[i+1];
                    }
					if ((*actors_size) > 1) {
                    	(*actors_size)--;

                    	//Free the empty space since an actor has been deleted
                    	actors = realloc(actors, ( (*actors_size) * sizeof(Actor)));
					}
                    break;

                case 'N':
                    printf("\nProcess aborted.");
                    break;
            }
        }
		} else {
            if (pos == -1) {
                printf("\nActor with attribute %s was not found in the system.\n", token);
            }
        }

    }


}




/*******************
 * @Purpose: Change certain attributes from an actor
 * @Parameters: in - actors: array with all actors
 *                 - pos: position of the actor to change in the array
 * @Return: ----
 * @Author: Ivan Fernandez
 *******************/
void changeActor(Actor *actors[], int pos) {
    char option[MAXCHAR];

	do {
        printf("Modifying actor (%d), %s %s.\n", actors[pos]->id, actors[pos]->name, actors[pos]->surname);

    	printf("What needs to be modified?\n");
    	printf("\t1.Modify ID.\n");
    	printf("\t2.Modify Name.\n");
    	printf("\t3.Modify Surname.\n");
    	printf("\t4.Modify phone number.\n");
    	printf("\t5.Exit.\n");
    	printf("Select an Option: ");

    
        scanf("%s", option);
        if (!checkInteger(option)) {
            option[0] = '6';
        }
        switch (option[0]) {
            case '1':
                printf("\nIntroduce the new ID: ");
                char id[MAXCHAR];
                scanf("%s", id);
                if (checkInteger(id)) {
                    actors[pos]->id = atoi(id);
                } else {
                    printf("\nError, invalid ID!\n");
                }
                break;

            case '2':

                printf("Introduce new name: ");
                char name[MAXCHAR];
                scanf("%s", name);

                strcpy(actors[pos]->name, name);
                break;

            case '3':

                printf("Introduce new surname: ");
                char surname[MAXCHAR];
                scanf("%s", surname);

                strcpy(actors[pos]->surname, surname);
                break;

            case '4':
                printf("Introduce new Phone Number: ");
                char phone_num[MAXCHAR];
                scanf("%s", phone_num);
                if (checkInteger(phone_num)) {
                    actors[pos]->phone = atoi(phone_num);
                } else {
                    printf("Error, invalid Phone Number!");
                }
                break;

            case '5':
                printf("\nExiting menu...\n");
                break;

            default:
                printf("\nSelect a valid input: ");
                option[0] = '6';
                break;
        }
    } while (option[0] != '5');

} //End of changeActor






/*******************
 * @Purpose: Display contents of an array of actors with unknown size
 * @Parameters: in - actors: array with all actors
 * @Return: ----
 * @Author: Ivan Fernandez
 *******************/
void displayActors(Actor actors[], int *actors_size) {

    for (int i=0; i<(*actors_size); i++) {
        printf("\nActor: %s, %s  (%d)", actors[i].surname, actors[i].name, actors[i].id);
        printf("\n\tHiring: +34(%d) || %d$\n", actors[i].phone, actors[i].salary);
    }

}


