//
// Created by ivanf_uunngm1 on 1/14/2024.
//

#ifndef LSTELEVISION_BUDGET_H
#define LSTELEVISION_BUDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 25
typedef char String[MAXCHAR];

void checkBudget(float *budget); //Prints the current budget


/*********************************************************************
 * @Purpose: Get the budget from the persistence file
 * @Parameters: ----
 * @Returns: the current budget of LSTelevision
 * @Author: Spencer
 *********************************************************************/
float getBudgetsInSystem();


/*********************************************************************
 * @Purpose: Register the expense in the database
 * @Parameters: in: item = string specifying the type of expense
 *              in: money = cost of the expense, to be withdrawn from budget
 * @Returns: ----
 * @Author: Ivan Fernandez
 *********************************************************************/
void registerExpense(String item, float money);


/*********************************************************************
 * @Purpose: Register the revenue in the database
 * @Parameters: in: item = string specifying the type of revenue
 *              in: money = revenue obtained, to be added to budget
 * @Returns: ----
 * @Author: Ivan Fernandez
 *********************************************************************/
void registerIncome(String item, float money);

#endif //LSTELEVISION_BUDGET_H
