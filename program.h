//
// Created by Ivan Fernandez on 1/5/2024.
//
#ifndef FOR_STORIES_PROGRAM_H
#define FOR_STORIES_PROGRAM_H

#include "format_checking.h"
#include "actor.h"
#include "limits.h"

#define MAXACTORS 3
#define MAXCHAR 25

#define COMEDY 0
#define TRAGEDY 1
#define SITCOM 2
#define DOCUMENTAL 3
#define DRAMATIC 4
#define FICTION 5
#define REAL_BASED 6
#define SCIENCE_FI 7
#define HISTORICAL 8
#define COCKING 9
#define OTHER 10


typedef char String[MAXCHAR];

typedef struct {
    String name;
    String actors[3];
    int time_broadcast;
    String channel_name;
    int num_actors;
    int category;
    int duration;
} Program;

int searchProgram(String program_str);

int cancelProgram(int program_size, Program programs[], String program);

Program addNewProgram();

void displayPrograms(Program programs[], int program_size);

void searchByFilter(Program programs[], int program_size);

void saveToFileProg(int programs_size, Program programs[]);

Program* readAllPrograms(int* programs_size);


#endif //FOR_STORIES_PROGRAM_H
