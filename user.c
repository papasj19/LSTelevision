
#include "user.h"

/*************
* @Purpose: Get all users from the database
* @Parameters: in: ----
* @Returns: users from the database
* @Author: Ivan Fernandez
**************/
User* readAllUsers(int *users_size) {
    FILE *fp;
    User* users;
    char tmp[MAXCHAR];
	char aux;
    int i, j;

    users = (User*) malloc(sizeof(User));
	(*users_size) = 0;

    fp = fopen("userfile.txt", "r");

    if (fp != NULL) {

        // Get number of users
        fscanf(fp, "%s", tmp);
        fscanf(fp, "%c", &aux);

        if (!feof(fp)) {
            *users_size = atoi(tmp);
            users = realloc(users, ((*users_size) * sizeof(User)));
        }

        //Read ID
        fscanf(fp, "%s", tmp);
        fscanf(fp, "%c", &aux);

        while(!feof(fp)) {

            for (i=0; i<(*users_size); i++) {
                //Get the ID
                strcpy(users[i].id, tmp);

                // Set the type of User based on the ID
                if (users[i].id[0] == 'P') {
                    users[i].type = PRODUCER;
                } else {
                    users[i].type = CLIENT;
                }

                //Get name
                fgets(tmp, MAXCHAR, fp);
                tmp[strlen(tmp) - 1] = '\0';
                strcpy(users[i].name, tmp);

                //Get email
                fscanf(fp, "%s", tmp);
                fscanf(fp, "%c", &aux);
                strcpy(users[i].email, tmp);

                //Get password
                fgets(tmp, MAXCHAR, fp);
                tmp[strlen(tmp) - 1] = '\0';
                strcpy(users[i].password, tmp);

                // Get separator from next User
                fscanf(fp, "%c", &aux);


                //Get Id before ending
                fscanf(fp, "%s", tmp);
                fscanf(fp, "%c", &aux);
            }



        }
        return users;
    }

	free(users);
    return NULL;

}

/*************
* @Purpose: Save all the users and the changes done to the database
* @Parameters: in: users - array of User with all the users
*                  user_size - number of users in the database
* @Returns: ----
* @Author: Ivan Fernandez
**************/
void updateDatabaseUser(User users[], int user_size) {
    FILE *fp;
    int i;

    fp = fopen("userfile.txt", "w");
    if (fp != NULL) {

        // Save number of users
        fprintf(fp, "%d\n\n", user_size);

        // Save Users
        for (i=0; i<user_size; i++) {
            fprintf(fp, "%s\n%s\n%s\n%s\n\n", users[i].id, users[i].name, users[i].email, users[i].password);
        }


    }



}

//function to obtain the information required to create a new user l
 User addNewUser(int mode){
    User new_user;
    char tmp[MAXCHAR];
	char type[MAXCHAR];

	do {
        printf("\nPlease enter the desired id: ");
        scanf("%s",tmp);
	} while (!checkInt(tmp));

    //Saves if the user is a Producer on a Client depending on the program mode
    if (mode == 1) {
		strcpy(type, "C");
		strcat(type, tmp);
        strcpy(new_user.id, type);

		new_user.type = CLIENT;
    } else {
		strcpy(type, "P");
		strcat(type, tmp);
        strcpy(new_user.id, type);

		new_user.type = PRODUCER;
    }

    do {
        printf("Please enter the desired email: ");
        scanf("%s",new_user.email);
    } while (!checkEmail(new_user.email));

    printf("Please enter your name: ");
    scanf("%s",new_user.name);

    printf("Please enter your password: ");
    scanf("%s",new_user.password);

    return new_user;
}


User registerNewUser(int *valid, int mode){
	User u = addNewUser(mode);

    if(askForSure("Are you sure? (Y/N): ")){
        printf("\n Registered Successfully!");
        (*valid) = 1;
    }else{
        printf("\n An Error has occured :(\n");
        (*valid) = 0;
	}

	return u;
}



/*****************************************************
* @Objective: Receive and save user credentials
* @Parameters: in: ----
*              out: user_login - user credentials
* @Return: User structure with the user credentials
*****************************************************/
User getUserLogin() {
    User user_login;               //Gets the user email and password for then to be checked

    printf("\nPlease, introduce your credentials.\n");

    printf("\tEnter your email: ");
    scanf("%s", user_login.email);

    printf("\tEnter your password: ");
    scanf("%s", user_login.password);

    return user_login;

}



/*****************************************************
* @Objective: Check for the user in the database
* @Parameters: in: login - user to be checked
*                  validation - correctness of credentials passed by reference
*                  users - dynamic array with the users from the database
*              out: login - current user using the program
* @Return: User structure with the user credentials
*****************************************************/
User checkLogin(User users[], User login, int *validation, int users_size) {
    int flag = 0;                               //Indicates if the user wit the given credentials exists in the file
    int i;                                      //Index that passes through arrays


    //Searches for the user in the program to check if it exists
    for (i=0; i<users_size; i++) {
        if (!strcmp(login.email, users[i].email) && !strcmp(login.password, users[i].password) && flag == 0) {
            *validation = 1;            //Login successful
            //Fill rest of the user information
            strcpy(login.id, users[i].id);

            if (login.id[0] == 'P') {
                login.type = PRODUCER;
            } else {
                login.type = CLIENT;
            }

            strcpy(login.name, users[i].name);

            flag++;

        }
    }

    if (flag != 1) {
        *validation = 0;
    }

	return login;
}


/*****************************************************
* @Objective: Redirect the user depending on the output of its Login
* @Parameters: in: users - dynamic array with the users from the database
*              out: u - user information
* @Return: To finish
*****************************************************/
User loginUser(User users[], int users_size, int *valid) {
    User u;             //User logged into the program
    int validation;     //Indicates the redirection depending on credentials correctness and errors


    //Get user email and password
    u = getUserLogin();
    //Check for the correctness of them
    u = checkLogin(users ,u, valid, users_size);

    //Redirect user depending on the correctness of credentials and type of user
    switch (*valid) {
        //Incorrect Credentials
        case 0:
            printf("Incorrect email or password.\n");
            break;

        //Correct Credentials
        case 1:
            printf("Welcome %s, loading program...\n", u.name);
            break;

    }


    return u;
}

int askForSure(char message[]) {
    char sure[MAXCHAR];

    do {
        printf("%s", message);
        scanf("%s", sure);

        if (strlen(sure) > 1) {
            sure[0] = 'E';
        } else {
            sure[0] = toupper(sure[0]);
        }
    } while (sure[0] != 'Y' && sure[0] != 'N');

    if (sure[0] == 'Y') {
        return 1;
    }

    return 0;
}

/*****************************************************
* @Objective: check if the given string is an integer
* @Parameters: in: str - string to check
*              out: boolean integer meaning if the given str is an integer
* @Return: Boolean with the answer.
*****************************************************/
int checkInt(char str[]) {
    int i;

    for (i=0; i<strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }

    return 1;
}


/*****************************************************
* @Objective: check if the given string is a valid
*             email by checking the '@' and a '.' after the arroba
* @Parameters: in: str - string to check
*              out: boolean integer meaning if the given string is an email
* @Return: Boolean with the answer.
*****************************************************/
int checkEmail(char str[]) {
    int i, j;
    int flag = 0;

    for (i=0; i<strlen(str); i++) {
        if (str[i] == '@') {
            for (j=i; j<strlen(str); j++) {
                if (str[j] == '.') {
                    flag++;
                }
            }
        }
    }

    if (flag == 1) {
        return 1;
    }

    return 0;

}


