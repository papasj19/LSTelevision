#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "channel.h"
#include "creditCard.h"



void mainMenu();

void producerMenu();

void clientMenu();

int adMenu();

int channelMenu();

int programMenu();

int actorMenu();

void manageActorsMenu();

void searchActorByMenu();

void doMenu();

void clientMainMenu(Program** programs, int* progams_size, Channel** channels, int* channels_size, CreditCard** cards, int* size_CC);

int clientManageMenu();

void manageClientMenu();

void searchClientByMenu();

void modifyUserMenu();


#endif
