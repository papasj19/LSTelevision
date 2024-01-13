#include "channel.h"

/*-----------------------------------------------------------------------------------------------------------------------------
 Author: Alan
 Input: budget of the producers
 Output: information regarding the channel the producers want to create
 Functionality: asks the producers for information regarding the channel then returns it, so it can be saved in another function
-----------------------------------------------------------------------------------------------------------------------------*/
Channel grabInfo(float* budget, Channel channels[], int channel_size) {
    Channel grab_info;
    int i, confirmation = 0;       //"Confirmation" is for the user to confirm that the inputted information is correct
    int count = 0;
    
    if (channel_size == 0) {
        printf("ERROR opening channel file\n");
    }
    
    else {
        printf("\n-----------------------------------------------\n");
            
        while (confirmation == 0) {
            printf("Introduce the name of the channel: ");
            scanf("%s", grab_info.name);
            
            for (i = 0; i < channel_size; i++) {     //Checks if the name inputted is unique among all the channel names
                
                if (strcmp(channels[i].name, grab_info.name) == 0) {
                    count++;
                }
            }

            if (count > 0) {
                printf("Please introduce a unique channel name.\n");
                scanf("%s", grab_info.name);
                count = 0;
            }

            else {
                confirmation++;
            }
        }

        grab_info.cost = askForFloat("Please introduce the cost");
        *budget -= grab_info.cost * 2;       //Reduces the budget of the producer by two times of the subscription cost

        grab_info.prog_length = askForInteger("Introduce the amount of programs you want to have: ");
        
        printf("\n-----------------------------------------------\n");
    }

    return grab_info;
}

/*-----------------------------------------------------------------------------------------------------------------------------
 Author: Alan
 Input: void
 Output: void
 Functionality: saves all the info from the file then changes one thing and then replaces the previous file with the saved info
-----------------------------------------------------------------------------------------------------------------------------*/
void modifyChannel (Channel channels[], int channel_size, float *budget) {
    int i = 0;
    Channel modify_info;
    int modify_pos = -4;
        
    printf("Introduce the name of the channel you wish to modify: ");
    scanf("%s", modify_info.name);

    while (i < channel_size) {
        if (strcmp(modify_info.name, channels[i].name) == 0) {     //Looks for the position of the info that the user wants to change
            modify_pos = i;
        }

        i++;        //Counts down from the last piece of saved info
    }

    if (modify_pos < 0) {
        printf("There is no such channel.\n");
    }

    else {
        //modify_info = grabInfo(&budget, channels, channel_size);       //I reuse a function to get all the info the user wants to modify

        printf("The previous name was: %s\n", channels[modify_pos].name);
        printf("Please introduce the new name: ");
        scanf("%s", modify_info.name);

        strcpy(channels[modify_pos].name, modify_info.name);        //Replace that info with the new info we just got

        printf("The previous cost was: %.2f\n", channels[modify_pos].cost);
        *budget += channels[modify_pos].cost * 2;
        modify_info.cost = askForFloat("Please introduce a new cost: ");
        channels[modify_pos].cost = modify_info.cost;
        *budget -= channels[modify_pos].cost * 2;

        modify_info.prog_length = 0;
        while (modify_info.prog_length > 12 || modify_info.prog_length < 1) {
            printf("The previous program length was: %d\n", channels[modify_pos].prog_length);
            modify_info.prog_length = askForInteger("Please introduce a new program length: ");

            if ( !(modify_info.prog_length <= 12 && modify_info.prog_length > 0) ) {
                printf("The amount of programs has to be between 1 and 12.\n");
            }
        }
        channels[modify_pos].prog_length = modify_info.prog_length;
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------
 Author: Alan
 Input: info of the channel
 Output: void
 Functionality: takes the information of the channel and saves it to the file
-----------------------------------------------------------------------------------------------------------------------------*/
int createChannel(Channel channels[], int channel_size, float *budget) {
    FILE* fp;
    int i;
    Channel grab_info;

    channels = (Channel *) realloc(channels, sizeof(Channel) * ( channel_size + 1));
    grab_info = grabInfo(budget, channels, channel_size);

    strcpy(channels[channel_size].name, grab_info.name);
    channels[channel_size].cost = grab_info.cost;

    channels[channel_size].prog_length = grab_info.prog_length;

    channel_size++;

    return channel_size;
}

/*-----------------------------------------------------------------------------------------------------------------------------
 Author: Alan
 Input: array of channels where all the info is stored
 Output: amount of channels in the array
 Functionality: takes the information of the file and saves it to the array
-----------------------------------------------------------------------------------------------------------------------------*/
Channel* readAllChannels(int* channels_size, Program programs[], float *budget) {
    Channel* channels;
    FILE *fp;
    int channel_size;
    int i, j = 0;

    fp = fopen("channelfile.txt", "r");

    if (fp == NULL) {
        printf("ERROR opening the file.\n");
    }

    else {
        fscanf(fp, "%d", &channel_size);

        channels = (Channel*) malloc (sizeof(Channel) * channel_size);
        while (!feof(fp)) {
            fscanf(fp, "%s", channels[j].name);

            if (!feof(fp)) {
                fscanf(fp, "%f", &channels[j].cost);
                *budget -= channels[j].cost * 2;

                fscanf(fp, "%d", &channels[j].prog_length);

                for (i = 0; i < channels[j].prog_length; i++) {
                    fscanf(fp, "%s", channels[j].programs_str[i]);

                    int pos = searchProgram(channels[j].programs_str[i]);
                    channels[j].programs[j] = programs[pos];
                }

                fscanf(fp, "%d", &channels[j].num_sub);
                for (i = 0; i < channels[j].num_sub; i++) {
                    fscanf(fp, "%s", channels[j].subscribers[i]);
                }
                j++;
            }
        }

        return channels;
    }

    return NULL;
}

void listChannelByAudience(int channel_size, Channel channels[]){
    int i, j, t = 0;
    for (i = 0; i < channel_size; i++) {
        for (j = i + 1; j < channel_size; j++) {
            if (channels[i].num_sub < channels[j].num_sub) {
                t = channels[i].num_sub;
                channels[i].num_sub = channels[j].num_sub;
                channels[j].num_sub = t;
            }
        }
    }
    // printing the output
    for (i = 0; i < channel_size; i++) {
        printf("%d ", channels[i]);
    }
}


void saveChannelToFile(int channel_size, Channel channels[]) {
    FILE *fp;
    int i, j;

    fp = fopen("channelfile.txt", "w");

    if (fp == NULL) {
        printf ("Error creating the file.\n");
        return;
    }

    else {
        fprintf(fp, "%d", channel_size);

        for (i = 0; i < channel_size; i++) {
            fprintf(fp, "%s", channels[i].name);
            fprintf(fp, "%f", channels[i].cost);
            fprintf(fp, "%d", channels[i].prog_length);
            for (j = 0; j < channels[i].prog_length; j++) {
                fprintf(fp, "%s", channels[i].programs_str[j]);
            }
            //subscribers id
            fprintf(fp, "%d\n", channels[i].num_sub);
            for (j = 0; j < channels[i].prog_length; j++) {
                fprintf(fp, "%s\n", channels[i].subscribers[j]);
            }
        }

        free(channels);
    }
}

void addProgramToChannel(int channel_size, Channel channels[], Program programs[], int program_size) {
    Program temp;
    String name;
    int i;
    int correct = 0;

    temp = addNewProgram();
    printf("Please introduce the name of the channel you want to add the program to: ");

    while (correct == 0) {
        scanf("%s", name);

        for (i = 0; i < channel_size; i++) {

            if (strcmp(channels[i].name, name) == 0) {
                correct = i;
            }
        }

        if (correct == 0) {
            printf("Please introduce the name of a channel that exists: ");
        }
    }

    channels[correct].programs[channels[correct].prog_length] = temp;
    channels[correct].prog_length++;
}

int deleteChannel(int channel_size, Channel channels[], int index, float *budget) {
    int i;

    if (index < 0 || index >= channel_size) {
        printf("Invalid index\n");
        return channel_size;
    }

    else {
        *budget += channels[index].cost * 2;

        for (i = index; i < channel_size; i++) {
            channels[i] = channels[i + 1];
        }

        channel_size--;
    }
}

void listChannels(int channel_size, Channel channels[]) {
    int option;
    int i;

    printf("How do you want to sort the channels?\n");
    printf("\t1. By audience\n");
    printf("\t2. By channel name\n");

    while (option != 1 && option != 2) {
        option = askForInteger("How do you want to sort the channels?\n\t1. By audience\n\t2. By channel name\t\n");
    }

    if (option == 1) {
        //To be done
    }

    else {
        for (i = 0; i < channel_size; i++) {
            i = insertionSort(channels, i, 0);
        }

        for (i = 0; i < channel_size; i++) {
            printf("Channel %d: %s", i, channels[i].name);
        }
    }
}

int insertionSort(Channel channels[], int i, int pos) {
    Channel temp;

    if (toupper(channels[i].name[pos]) == toupper(channels[i + 1].name[pos])) { //If the first letter is the same check the next letter
        i = insertionSort(channels, i, pos + 1);

        return i;
    }

    if (toupper(channels[i].name[pos]) > toupper(channels[i + 1].name[pos])) { //Compares the first letter of the first word and the one after it
        //I use upper to make sure that the comparison of the ASCII is fair
        temp = channels[i]; //I switch the words around if the criterion is met
        channels[i] = channels[i + 1];
        channels[i + 1] = temp;

        if (i > 1) { //I do this so I can compare the one I just switched with the previous word
            i -= 2;  //So I switch word[3] with word[2] now word[3] is word[2] so I need to compare the new word[2] and word[1]
        }

        if (i == 1) {
            i = -1;
        }
    }

    return i;
}

void listPrograms(int channel_size, Channel channels[]) {

    int i;
    int confirmation = -1;
    String name;

    while (confirmation < 0) {
        printf("Introduce the name of the channel: ");
        scanf("%s", name);

        for (i = 0; i < channel_size; i++) {     //Checks if the name inputted is unique among all the channel names

            if (strcmp(channels[i].name, name) == 0) {
                confirmation = i;
            }
        }

        if (confirmation < 0) {
            printf("Please introduce a name of a channel that exists.\n");
        }
    }

    for (i = 0; i < channels[confirmation].prog_length; i++) {
        printf("Program %d: %s", i, channels[confirmation].programs_str[i]);
    }
}

int removeProgram(int channel_size, Channel channels[], int program_size, Program programs[]) {

    String program;
    int current = program_size;
    int current_j;
    int i, j;

    printf("Please introduce the name of the program you wish to cancel.\n");

    while (program_size == current) {
        scanf("%s", program);
        program_size = cancelProgram(program_size, programs, program);

        if (program_size == current) {
            printf("Please introduce a program that exists.\n");
        }
    }

    for (i = 0; i < channel_size; i++) {
        for (j = 0; j < channels[i].prog_length; j++) {
            if (strcmp(program, channels[i].programs_str[j]) == 0) {
                current = i;
                current_j = j;
            }
        }
    }

    for (j = current_j; j < channels[current].prog_length - 1; j++) {
        strcpy(channels[current].programs_str[j], channels[current].programs_str[j + 1]);
        channels[current].programs[j] = channels[current].programs[j + 1];
    }

    channels[current].prog_length--;

    return program_size;
}
