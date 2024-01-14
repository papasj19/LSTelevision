
#include "budget.h"

/*-----------------------------------------------------------------------------------------------------------------------------
 Author: Alan, Ivan
 Input: void
 Output: void
 Functionality: prints out all the expenses and revenue then calculates budget and prints that out as well
-----------------------------------------------------------------------------------------------------------------------------*/
void checkBudget(float *budget) {
    FILE *fp;
    float money;
    float m_total = 0;
    String item;
    char aux;

    fp = fopen("expenses.txt", "r");

    if (fp == NULL) {
        printf("ERROR opening the file");
    }

    else {

        while (!feof(fp)) {     //Prints out every individual item and their cost
            fscanf(fp, "%s", item);
            fscanf(fp, "%c", &aux);
            fscanf(fp, "%f", &money);
            fscanf(fp, "%c", &aux);

            printf("%s cost you %f euros.\n", item, money);
            m_total += money;       //Adds all the expenses
        }

        printf("\nAll of these expenses add up to %f euros.\n", m_total);
        fclose(fp);
    }

    *budget -= m_total;     //Expenses subtracted from budget
    m_total = 0;

    fp = fopen("revenue.txt", "r");

    if (fp == NULL) {
        printf("ERROR opening the file");
    }

    else {

        while (!feof(fp)) {
            fscanf(fp, "%s", item);
            fscanf(fp, "%c", &aux);
            fscanf(fp, "%f", &money);
            fscanf(fp, "%c", &aux);

            printf("%s cost you %f euros.\n", item, money);
            m_total += money;
        }

        printf("\nYour revunue add up to %f euros.\n", m_total);
        fclose(fp);
    }

    *budget += m_total;     //Profits added to budget
    printf("\n\nYour current budget is %f euros.\n", budget);
}



/*********************************************************************
 * @Purpose: Get the budget from the persistence file
 * @Parameters: ----
 * @Returns: the current budget of LSTelevision
 * @Author: Spencer
 *********************************************************************/
float getBudgetsInSystem() {
    FILE* fp;
    float budget = 0;

    int count = 0;
    fp = fopen("budgetfile.txt", "r");
    if(fp != NULL){

        fscanf(fp, "%f", &budget);

        fclose(fp);

    }

    return budget;

}



/*********************************************************************
 * @Purpose: Register the expense in the database
 * @Parameters: in: item = string specifying the type of expense
 *              in: money = cost of the expense, to be withdrawn from budget
 * @Returns: ----
 * @Author: Ivan Fernandez
 *********************************************************************/
void registerExpense(char item[], float money) {
    FILE *fp;

    fp = fopen("expenses.txt", "a");

    if (NULL != fp) {
        fprintf(fp, "%s\n%f\n", item, money);
        fclose(fp);
    } else {
        printf("\n\nError opening the file\n\n");
    }

}


/*********************************************************************
 * @Purpose: Register the revenue in the database
 * @Parameters: in: item = string specifying the type of revenue
 *              in: money = revenue obtained, to be added to budget
 * @Returns: ----
 * @Author: Ivan Fernandez
 *********************************************************************/
void registerIncome(char item[], float money) {
    FILE *fp;

    fp = fopen("revenue.txt", "a");

    if (NULL != fp) {
        fprintf(fp, "%s\n%f\n", item, money);
        fclose(fp);
    } else {
        printf("\n\nError opening the file\n\n");
    }

}