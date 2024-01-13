#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program.h"
#include "format_checking.h"

#define MAXCHAR 25

typedef char String[MAXCHAR];

typedef struct {
    char name[MAXCHAR];
    float cost;
    Program programs[12];
    String programs_str[12];
    int prog_length;
    int num_sub;
    String subscribers[10];
} Channel;

void listChannelByAudience(int channel_size, Channel channels[]);

Channel grabInfo(float* budget, Channel channels[], int channel_size); //Function to ask the user for information regarding the channel they want to create

int createChannel(Channel channels[], int channel_size, float *budget); //Function to save the information introduce by the user to the channelInfo file

void modifyChannel(Channel channels[], int channel_size, float *budget); //Function to modify the information in the file of a specific channel

Channel* readAllChannels(int* channels_size, Program Programs[], float *budget); //Function to store all the info of the channel

void saveChannelToFile(int channel_size, Channel channels[]); //Function to transfer the array data back to the file

void addProgramToChannel(int channel_size, Channel channels[], Program programs[], int program_size);

int deleteChannel(int channel_size, Channel channels[], int index, float *budget); //Returns the new channel size

void listChannels(int channel_size, Channel channels[]);

int insertionSort(Channel channels[], int i, int pos); //Returns the current index for continued sorting

void listPrograms(int channel_size, Channel channels[]);

int removeProgram(int channel_size, Channel channels[], int program_size, Program programs[]); //Returns the new program size

#endif
