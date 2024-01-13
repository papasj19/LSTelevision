#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "channel.h"

int subscribeToChannel(User current_user, Channel current_channel);
int checkPin(char* pin, User current_user);
void saveSubscriptionDatabase(User current_user, Channel current_channel);

#endif //SUBSCRIBE_H
