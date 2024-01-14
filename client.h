
#ifndef FOR_STORIES_CLIENT_H
#define FOR_STORIES_CLIENT_H

#define MODIFY 0
#define DELETE 1


#include "user.h"
#include "menu.h"
#include "format_checking.h"


void manageClients(User *users[], int *users_size);
void displayClients(User users[], int size);
void manageClient(User *users[], int *users_size, int mode);
void changeUser(User *users[], int *users_size, int pos);


#endif //FOR_STORIES_CLIENT_H
