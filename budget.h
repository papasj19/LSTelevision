//
// Created by ivanf_uunngm1 on 1/14/2024.
//

#ifndef LSTELEVISION_BUDGET_H
#define LSTELEVISION_BUDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 50
typedef char String[MAXCHAR];

void checkBudget(float *budget); //Prints the current budget
float getBudgetsInSystem();
void registerExpense(String item, float money);
void registerIncome(String item, float money);

#endif //LSTELEVISION_BUDGET_H
