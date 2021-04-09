#include <stdio.h>
#include <stdlib.h>

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

    // if one node is exist in the linked list
    if (top->count < 0 || top->link == NULL) {
        return -1;
    }
    
    int returnValue = top->link->digit;

    // if there are more than one nodes in the linked list
    if (top->count == 0 || top->link->link == NULL) {
        free(top->link);
        return returnValue;
    }

    NODE *temp = top->link;
    top->link = temp->link;

    free(temp);
    return returnValue;
}

int getTop(TOP *top) {
    if (top->count <= 0 || top->link == NULL) {
        return -1;
    }

    return top->link->digit;
}

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

    if (top->link == NULL) {
        free(top);
        return;

    } else {
        NODE *temp = top->link;

        // if there is a node in the linked list        
        if (temp->link == NULL && top->count == 0) {
            free(temp);
            free(top);
            return;
        }

        // else, there are more than one nodes in the linked list
        temp = temp->link;
        free(temp);
    }

    return;
}

int main() {
    TOP *stk = createStack();

    push(stk, 10);
    push(stk, 20);
    printf("%d\n", getTop(stk));
    push(stk, 30);
    printf("%d\n", pop(stk));
    push(stk, 40);
    push(stk, 50);
    printStack(stk);
    freeStack(stk);
}