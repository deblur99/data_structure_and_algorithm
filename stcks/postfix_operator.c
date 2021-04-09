#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 2
#define MAX_STRING_SIZE 100
#define RESULT_STRING_SIZE 20

typedef struct node {
    int digit;
    struct node *link;
}NODE;

typedef struct top {
    int count;
    struct node *link;
}TOP;

TOP* createStack() {
    
    TOP *top = malloc(sizeof(TOP));
    top->count = 0;
    top->link = NULL;

    return top;
}

void push(TOP *top, int input) {

    top->count++;

    NODE *newNode = malloc(sizeof(NODE));

    newNode->digit = input;
    newNode->link = top->link;

    top->link = newNode;

    return;
}

int pop(TOP *top) {

    top->count--;

    // if no one node is exist in the linked list
    if (top->count < 0) {
        return -1;
    }
    
    int returnValue = top->link->digit;

    NODE *temp = top->link->link;
    free(top->link);
    top->link = temp;

    return returnValue;
}

// debug
void printStack(TOP *top) {

    NODE *temp = top->link;

    while (temp != NULL) {
        printf("%d ", temp->digit);
        temp = temp->link;
    }

    printf("\n");

    return;
}

void freeStack(TOP *top) {

    // if there is a node in the linked list        
    if (top->link == NULL) {
        free(top);
        return;

    } else {
        NODE *temp = top->link;

        // else, there are more than one nodes in the linked list
        while (temp->link != NULL) {
            temp = temp->link;
            free(top->link);
            top->link = temp;
        }
    }

    free(top);

    return;
}

int getAmount(FILE *fp);

int main() {
    FILE *fp = fopen("data_structure_and_algorithm/stcks/input.txt", "r");
    FILE *fp2 = fopen("data_structure_and_algorithm/stcks/output.txt", "w");

    int amount = getAmount(fp);
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    char *str = malloc(sizeof(char) * MAX_STRING_SIZE);
    char *result_str = malloc(sizeof(char) * RESULT_STRING_SIZE);
    TOP* stack = NULL;
    int pop1 = 0; int pop2 = 0; int calc = 0; int result = 0;

    memset(buffer, 0, BUFFER_SIZE);
    memset(str, 0, MAX_STRING_SIZE);
    memset(result_str, 0, RESULT_STRING_SIZE);
    
    printf("%d\n", amount); // debug

    // get a line which indicates terms from input.txt
    while (amount > 0) {
        amount--;

        while (strcmp(buffer, "\n") != 0) {
            fread(buffer, sizeof(char), 1, fp);

            if (strcmp(buffer, "\n") != 0)
                strcat(str, buffer);
        }

        stack = createStack();
        
        for (int i = 0; i < strlen(str); i++) {

            if (isdigit(str[i])) {
                push(stack, str[i] - '0');
            }
            
            else if (str[i] == '+' || str[i] == '-' || str[i] == '*') {
                pop1 = pop(stack);
                pop2 = pop(stack);
                calc = 0;

                switch (str[i]) {
                    case '+':
                        calc = pop2 + pop1;
                        push(stack, calc);
                        break;
                        
                    case '-':
                        calc = pop2 - pop1;
                        push(stack, calc);
                        break;

                    case '*':
                        calc = pop2 * pop1;
                        push(stack, calc); 
                        break;
                }
            }
        }

        // exception
        if (stack->count > 1) {
            strcpy(result_str, "0\n");
        }
        
        else {
            result = pop(stack);
            sprintf(result_str, "%d\n", result);
        }

        fwrite(result_str, sizeof(char), strlen(result_str), fp2);

        freeStack(stack);
        
        memset(buffer, 0, BUFFER_SIZE);
        memset(str, 0, MAX_STRING_SIZE);
        memset(result_str, 0, RESULT_STRING_SIZE);
    }

    free(result_str); free(str); free(buffer);
    fclose(fp2); fclose(fp);

    return 0;
}

int getAmount(FILE *fp) {

    int amount = 0;

    char *buffer = malloc(sizeof(char) * 2);
    char *str = malloc(sizeof(char) * 20);
    
    while (strcmp(buffer, "\n") != 0) {
        fread(buffer, sizeof(char), 1, fp);
        strcat(str, buffer);
    }

    amount = atoi(str);
    
    free(str); free(buffer);

    return amount;
}