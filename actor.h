#ifndef ACTOR_H_
#define ACTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "format_checking.h"

#define _OPEN_SYS_ITOA_EXT
#define MAXCHAR 25

typedef struct {
        int id;
        char name[MAXCHAR];
        char surname[MAXCHAR];
        int phone;
        int salary;
        char program[MAXCHAR];
} Actor;

Actor* readAllActors(int *actors_size);

void updateDatabaseActors(Actor *actors[], int *actors_size);

int checkDigits(int to_check); //used to check

Actor RecInfo(); //utilizes console to recieve information about an actor from the user

void registerNewActor(); //manages the result of the systems ability to write the to the actor file and notifies the user of the result

int addNewActorToFile(Actor to_be_written);//opens and closes the file as well as writing the information of a new actor to the file

void displayUnemployedActors(Actor actors[], int *actors_size);

int getActorFromUser(Actor *actors[], int *actors_size);

void hireActor(Actor *actors[], char program[], int pos);

void actorsOptions(Actor *actors[], int *actors_size);

void manageActors(Actor *actors[], int mode, int *actors_size);

void changeActor(Actor *actors[], int pos);

void displayActors(Actor actors[],  int *actors_size);

int checkInteger(char str[]);

Actor addNewActor(Actor actors[], int actors_size);


#endif
