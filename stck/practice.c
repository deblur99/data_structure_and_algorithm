#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
}NODE;

typedef struct head {
    int count;
    NODE *link;
}HEAD;

HEAD* createStack() {
    HEAD *head = (HEAD *)malloc(sizeof(HEAD));

    head->count = 0;
    head->link = NULL;

    return head;
}

void pushStack(HEAD *head, int data) {

    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    newNode->data = data;

    if (head->link == NULL) {
        head->link = newNode;
        newNode->link = NULL;
    } else {
        newNode->link = head->link;
        head->link = newNode;
    }

    (head->count)++;

    return;
}

int popStack(HEAD *head) {

    int tempData = head->link->data;
    NODE *tempLink;

    if (head->link->link == NULL) {
        free(head->link);
        head->link = NULL;
        free(head);
    }
    
    else {
        tempLink = head->link;
        head->link = head->link->link;
        tempLink->link = NULL;
        free(tempLink);
    }

    (head->count)--;

    return tempData;
}

void printStack(HEAD *head) {

    NODE *temp = head->link;

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }

    return;
}

void freeStack(HEAD *head) {

    NODE *temp;

    while (head->link->link != NULL) {
        temp = head->link;
        head->link = head->link->link;
        temp->link = NULL;
        free(temp);
    }

    free(head->link);
    free(head);

    return;
}

int main() {

    HEAD *head = createStack();

    int stackLimit = 5, inputData;

    while (stackLimit > 0) {
        scanf("%d", &inputData);
        pushStack(head, inputData);
        printStack(head);
        printf("\n");
        stackLimit--;
    }

    printf("Stack count: %d\n", head->count);
    printStack(head);
    printf("\n");

    popStack(head);
    printStack(head);
    printf("\n");

    popStack(head);
    printStack(head);
    printf("\n");

    popStack(head);
    printStack(head);
    printf("\n");

    popStack(head);
    printStack(head);
    printf("\n");

    freeStack(head);

    return 0;
}