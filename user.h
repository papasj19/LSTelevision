#ifndef USER_H_
#define USER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PRODUCER 0
#define CLIENT 1
#define MAXCHAR 25

typedef struct {
    int type;
    char id[MAXCHAR];
    char name[MAXCHAR];
    char email[MAXCHAR];
    char password[MAXCHAR];
   // CreditCard card;
} User;

User* readAllUsers(int *users_size);

void updateDatabaseUser(User users[], int user_size);

User addNewUser(int mode);

int addNewUserToFile(User to_be_written);

User registerNewUser(int *valid, int mode);

User getUserLogin();

User checkLogin(User users[], User login, int *validate, int users_size);

User loginUser(User users[], int users_size, int *valid);


int askForSure(char message[]);

int checkInt(char str[]);

int checkEmail(char str[]);

#endif
