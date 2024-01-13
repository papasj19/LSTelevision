//
//  program.c
//
//
//  Created by Spencer Johnson on 1/2/24.
//

#include "program.h"


int searchProgram(String programs_str){
    return 0;
}

int cancelProgram(int program_size, Program programs[], String program){
    return 0;
}



/*----------------------------------------------
 Author: spencer
 Input: void
 Output: the newly recieved info as a Program
 Functionality: convert console info into a program
----------------------------------------------------*/
Program addNewProgram(){
    Program temp;
    char answer;
    char trash;
    char time[MAXCHAR];
    char duration[MAXCHAR];
    char numAct[MAXCHAR];
    char cat[MAXCHAR];

    printf("Enter the name: ");
    scanf("%s", temp.name);
    /*
     * print channels
     * ask user for channel int
     * save that name of channel to the program.channel_name
     */
    temp.category = askForInteger("Enter the category: ");
    temp.time_broadcast = askForInteger("Enter the broadcast time in format HH: ");
    temp.duration = askForInteger("Enter the duration of the program: ");
    printf("Would you like to add actors now? (Y/N): ");
    scanf("%c", &answer);
    scanf("%c", &trash);
    if(answer == 'y' || answer == 'Y'){
        temp.num_actors = askForInteger("How many actors?: ");
        for(int i = 0; i < temp.num_actors; i++){
            printf("Enter the actor name: ");
            scanf("%s", temp.actors[i]);
        }
    }else{
        temp.num_actors = 0;
    }
    return temp;
}

void displayProgramsByChannel(Program programs[], int program_size, String channel_name) {
    int i, j;

    for (i = 0; i < program_size; i++) {
        if(strcmp(programs[i].channel_name, channel_name) == 0) {

            //get current time from lib


            printf("%s\n", programs[i].name);
            printf("%d minutes.\n", programs[i].duration);

            for (j = 0; j < programs[i].num_actors; j++) {
                printf("\t>%s\n", programs[i].actors[j]);
            }

            switch (programs[i].category) {
                case 0:
                    printf("Comedy\n");
                    break;
                case 1:
                    printf("Tragedy\n");
                    break;
                case 2:
                    printf("SitCom\n");
                    break;
                case 3:
                    printf("Documentary\n");
                    break;
                case 4:
                    printf("Drama\n");
                    break;
                case 5:
                    printf("Fiction\n");
                    break;
                case 6:
                    printf("Comedy");
                    break;
                case 7:
                    printf("SciFi\n");
                    break;
                case 8:
                    printf("Historical\n");
                    break;
                case 9:
                    printf("Cooking\n");
                    break;
                case 10:
                    printf("Other\n");
                    break;
            }
        }
    }

}



void displayPrograms(Program programs[], int program_size) {
    int i, j;

    for (i = 0; i < program_size; i++) {
        printf("%s\n", programs[i].name);
        printf("%d minutes.\n", programs[i].duration);

        for (j = 0; j < programs[i].num_actors; j++) {
            printf("\t>%s\n", programs[i].actors[j]);
        }

        switch (programs[i].category) {
            case 0:
                printf("Comedy\n");
                break;
            case 1:
                printf("Tragedy\n");
                break;
            case 2:
                printf("SitCom\n");
                break;
            case 3:
                printf("Documentary\n");
                break;
            case 4:
                printf("Drama\n");
                break;
            case 5:
                printf("Fiction\n");
                break;
            case 6:
                printf("Comedy");
                break;
            case 7:
                printf("SciFi\n");
                break;
            case 8:
                printf("Historical\n");
                break;
            case 9:
                printf("Cooking\n");
                break;
            case 10:
                printf("Other\n");
                break;
        }
    }

}


void searchByFilter(Program programs[], int program_size) {
    char tmp[MAXCHAR];                  // Used for diverse purposes, mainly check inputs format
    int temporal;                       // Same as tmp but as an integer
    char menu_option = '.';                   // Used for getting menu options selected by character coding
    Program *filtered_programs;         // Program array containing the programs that match the searching filter
    int i,j;                            // Index used for passing through different arrays
    int from, to;                       // Used for checking ranges
    int go_back = 0;                    // Explains if the user must go back to the previous section or ask again/kept in this menu

    // While user does not want to go back, keep asking for actions
    do {

        // Keep asking for an option until a valid one is received
        do {
            printf("\nSearch program by:\n");
            printf("\tA) Category.\n");
            printf("\tB) Duration.\n");
            printf("\tC) Actors.\n");
            printf("\tD) Name.\n\n");
            printf("\tE) Go Back.\n");
            printf("Select an option: ");

            scanf("%s", tmp);

            if (!checkCharacter(tmp)) {
                printf("Incorrect format input, try again!\n");
                printf("Please input: A, B, C, D or E.\n");
            } else {
                menu_option = toupper(tmp[0]);
            }


        } while (!checkCharacter(tmp) || menu_option < 'A' || menu_option > 'E');


        switch (menu_option) {
            case 'A':
                do {
                    printf("\nChoose a category:\n");
                    printf("\t1) Comedy\n");
                    printf("\t2) Tragedy\n");
                    printf("\t3) Sitcom\n");
                    printf("\t4) Documentary\n");
                    printf("\t5) Drama\n");
                    printf("\t6) Fiction\n");
                    printf("\t7) Real Based\n\n");
                    printf("\t8) Go Back\n");
                    printf("Select a category: ");

                    scanf("%s", tmp);

                    if (!checkInteger(tmp)) {
                        printf("Incorrect format, please try again\n");
                        printf("Please input a number from 1 to 8.\n");
                        temporal = 9;
                    } else {
                        temporal = atoi(tmp);
                    }

                } while (temporal < 1 || temporal > 8);

                if (temporal != 8) {
                    filtered_programs = (Program *) malloc(sizeof(Program));
                    j = 0;
                    for (i = 0; i < program_size; i++) {
                        if (programs[i].category == temporal) {
                            filtered_programs[j] = programs[i];
                            j++;
                            filtered_programs = (Program *) realloc(filtered_programs, j * sizeof(Program));
                        }
                    }

                    displayPrograms(filtered_programs, j);
                }

                break;


            case 'B':

                menu_option = '.';
                do {
                    printf("\nChoose an approximate duration (per episode):\n");
                    printf("\tA) less than 5 minutes\n");
                    printf("\tB) 5~10 minutes\n");
                    printf("\tC) 10~20 minutes\n");
                    printf("\tD) 20~30 minutes\n");
                    printf("\tE) 30~60 minutes\n");
                    printf("\tF) 60~90 minutes\n");
                    printf("\tG) more than 90 minutes\n\n");
                    printf("\tH) Go Back\n");
                    printf("Select a duration range: ");

                    scanf("%s", tmp);

                    if (!checkCharacter(tmp)) {
                        printf("Select a valid format, try again!\n");
                    } else {
                        menu_option = toupper(tmp[0]);
                    }
                } while (!checkCharacter(tmp) || menu_option < 'A' || menu_option > 'H');


                switch (menu_option) {
                    case 'A':
                        from = 0;
                        to = 5;
                        break;

                    case 'B':
                        from = 5;
                        to = 10;
                        break;

                    case 'C':
                        from = 10;
                        to = 20;
                        break;

                    case 'D':
                        from = 20;
                        to = 30;
                        break;

                    case 'E':
                        from = 30;
                        to = 60;
                        break;

                    case 'F':
                        from = 60;
                        to = 90;
                        break;

                    case 'G':
                        from = 90;
                        to = INT_MAX;
                        break;

                    default:
                        from = -1;
                        break;

                }

                if (from >= 0) {
                    filtered_programs = (Program *) malloc(sizeof(Program));
                    j = 0;
                    for (i = 0; i < program_size; i++) {
                        if (programs[i].duration >= from && programs[i].duration <= to) {
                            filtered_programs[j] = programs[i];
                            j++;
                            filtered_programs = (Program *) realloc(filtered_programs, j * sizeof(Program));
                        }
                    }

                    displayPrograms(filtered_programs, j);
                }


                break;

            case 'C':
                //to be decided
                break;

            case 'D':

                printf("\nIntroduce the program's name: ");
                scanf("%s", tmp);

                filtered_programs = (Program *) malloc(sizeof(Program));
                j = 0;
                for (i = 0; i < program_size; i++) {
                    if (strstr(programs[i].name, tmp) != NULL) {
                        filtered_programs[j] = programs[i];
                        j++;
                        filtered_programs = (Program *) realloc(filtered_programs, j * sizeof(Program));
                    }
                }

                displayPrograms(filtered_programs, j);

                break;


            case 'E' :
            default:
                go_back = 1;
                break;

        }

    } while (!go_back);


}

Program* readAllPrograms(int* programs_size) {
    Program* programs;
    FILE *fp;
    int i, j;
    char trash;
    int temp_size;


    programs = malloc(sizeof(Program));
    (*programs_size) = 0;

    fp = fopen("programfile.txt", "r");

    if (fp == NULL) {
        printf("Error opening the file.\n");
    }

    else {
        // Read how many Programs
        fscanf(fp, "%d", &temp_size);
        fscanf(fp, "%c", &trash);

        (*programs_size) = temp_size;
        programs = realloc(programs, ((*programs_size) * sizeof(Program)));

        for (i = 0; i < *programs_size; i++) {

            fscanf(fp,"%s", programs[i].name);
            fscanf(fp, "%c", &trash);

            fscanf(fp,"%s", programs[i].channel_name);
            fscanf(fp, "%c", &trash);

            fscanf(fp,"%d", &programs[i].category);
            fscanf(fp, "%c", &trash);

            fscanf(fp, "%d", &programs[i].duration);
            fscanf(fp, "%c", &trash);

            fscanf(fp, "%d", &programs[i].num_actors);
            fscanf(fp, "%c", &trash);

            for (j = 0; j < programs[i].num_actors; j++) {
                fscanf(fp, "%s", programs[i].actors[j]);
                fscanf(fp, "%c", &trash);
            }
        }
    }

    return programs;
}



//Saves the array into the file (rewrites the file)
void saveToFile(int programs_size, Program programs[]) {
    FILE *fp;
    int i, j;

    fp = fopen("programfile.txt", "w");

    if (fp == NULL) {
        printf("Error creating file.\n");
    }

    else {
        fprintf(fp, "%d\n\n", programs_size);

        for (i = 0; i < programs_size; i++) {
            fprintf(fp,"%s\n", programs[i].name);
            fprintf(fp,"%s\n", programs[i].channel_name);
            fprintf(fp,"%d\n", programs[i].category);
            fprintf(fp, "%d\n", programs[i].duration);
            fprintf(fp, "%d\n", programs[i].num_actors);

            for (j = 0; j < programs[i].num_actors; j++) {
                fprintf(fp, "%s ", programs[i].actors[j]);
            }
        }

        free(programs);
    }
}


//Dismisses the actor from the standpoint of the program
void dismissActor(int programs_size, Program programs[], Actor* actors, int *actors_size) {

    int i, j, count = 0;
    int pos;
    String prog_name;
    int prog_pos;

    String new_actors_str[MAXACTORS];
    Actor new_actors[MAXACTORS];

    printf("Introduce the name of the program you wish to dismiss the actor of.\n");
    scanf("%s", prog_name);

    for (i = 0; i < programs_size; i++) {
        if (strcmp(programs[i].name, prog_name) == 0) {
            pos = getActorFromUser(&actors, actors_size);
            count++;
            prog_pos = i;
        }
    }

    if (count == 0) {
        printf("There is no program with the name: %s\n", prog_name);
        return;
    }
    //remove the program from the actor
    strcpy(actors[pos].program, "");
    count = -1;
    j = 0;
    int auxpos = 0;
    for (i = 0; i < 3; i++) {
        int temp = atoi(programs[prog_pos].actors[i]);
        if (actors[pos].id == temp) {
            strcpy(programs[prog_pos].actors[i],"");
            auxpos = i;
        }
    }
    for(i = auxpos; i < 2; i++){
        strcpy(programs[prog_pos].actors[i],programs[prog_pos].actors[i+1]);
    }
    strcpy(programs[prog_pos].actors[2],"");

}
