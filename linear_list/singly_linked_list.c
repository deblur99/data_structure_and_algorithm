#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct _DATA {
    int num;
    char *name;
}DATA;

typedef struct _NODE {
    DATA data;
    struct _NODE *link;
}NODE;

typedef struct _HEAD {
    int count;
    struct _NODE *link;
}HEAD;

int checkFull(HEAD *head) {
    if (head->count >= MAX) {
        printf("List is full\n");
        return 0;
    } else if (head->count >= 0) {
        return 1;
    } else return 0;
}

HEAD* createList() {
    HEAD *head = malloc(sizeof(head));

    head->count = 0;
    head->link = NULL;

    return head;
}

void insertFirstNode(HEAD *head, DATA data) {
    if (checkFull(head)) {
        NODE *newNode = malloc(sizeof(NODE));

        newNode->data = data;
        newNode->link = head->link;
        head->link = newNode;

        head->count++;
    }

    return;
}

void insertLastNode(HEAD *head, DATA data) {
    if (checkFull(head)) {
        NODE *newNode = malloc(sizeof(NODE));

        newNode->data = data;

        NODE *pre = head->link;

        // 기존의 끝 노드 탐색
        while (pre->link != NULL) {
            pre = pre->link;
        }

        pre->link = newNode;
        newNode->link = NULL;

        head->count++;   
    }

    return;
}

void insertMiddleNode(HEAD *head, NODE *pre, DATA data) {
    if (pre == NULL) {
        printf("Can't input\n");
        return;
    }

    if (checkFull(head)) {
        NODE *newNode = malloc(sizeof(NODE));

        newNode->data = data;

        newNode->link = pre->link;
        pre->link = newNode;

        head->count++;
    }

    return;
}

void insertNode(HEAD *head, DATA data) {
    if (head->count == 0)
        insertFirstNode(head, data);
    
    else if (head->count < MAX)
        insertLastNode(head, data);
}

NODE* searchNode(HEAD *head, int find) {
    NODE *temp = head->link;

    while (temp->link != NULL && temp->data.num != find) {
        temp = temp->link;
    }

    if (temp->link == NULL) {
        printf("No result\n");
        return NULL;
    }

    return temp;
}

void deleteNode(HEAD *head, NODE *target) {
    if (target == NULL) {
        printf("Target is not selected\n");
        return;
    }

    // 맨 앞에서 삭제할 경우
    if (target == head->link) {
        head->link = target->link;
        free(target);
    }

    // 맨 뒤애서 삭제할 경우
    else if (target->link == NULL) {
        NODE *pre = head->link;
        
        while (pre->link != target) {
            pre = pre->link;
        }

        pre->link = NULL;
        free(target);
    }
    
    // 처음과 끝 사이에서 삭제할 경우
    else {
        NODE *pre = head->link;
        
        while (pre->link != target) {
            pre = pre->link;
        }

        pre->link = target->link;
        free(target);
    }

    head->count--;
    return;
}

void printList(HEAD *head) {
    NODE *temp = head->link;

    while (temp != NULL) {
        printf("Number: %d, Name: %s\n", temp->data.num, temp->data.name);
        temp = temp->link;
    }

    return;
}

void freeList(HEAD *head) {
    NODE *temp = head->link;

    while (temp->link != NULL) {
        temp = temp->link;
        free(head);
        head->link = temp;
    }

    head->count = 0;
    head->link = NULL;
    free(head);

    return;
}

int main() {
    HEAD *list = createList();
    DATA data1 = {10, "lee"};
    DATA data2 = {20, "kim"};
    DATA data3 = {30, "han"};
    DATA data4 = {40, "park"};
    DATA data5 = {50, "baek"};
    DATA data6 = {60, "yum"};

    insertFirstNode(list, data1);
    insertLastNode(list, data2);
    insertLastNode(list, data3);

    NODE *temp = searchNode(list, 20);
    insertMiddleNode(list, temp, data3);
    insertMiddleNode(list, temp, data4);
    temp = searchNode(list, 10);

    deleteNode(list, temp);
    insertFirstNode(list, data5);

    temp = searchNode(list, 20);
    deleteNode(list, temp);
    
    insertLastNode(list, data6);

    printList(list);
    freeList(list);

    return 0;
    /*
    int decision = 1;

    printf("1: continue, 2: quit\n");

    while (decision == 1) {
        printf("Select your choice: ");
        scanf("%d", &decision);

        if (decision == 2)
            break;

        else if (decision != 1) {
            printf("Invalid input\n");
            continue;
        }

        else {
            printf("Input number and name: ");
            scanf("%d %s", &inputData.num, inputData.name);

            insertFirstNode(list, inputData);
        }
    }
    */      
}