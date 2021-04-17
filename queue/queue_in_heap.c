#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct _DATA {
    int age;
    char name[10];
}DATA;

typedef struct _NODE {
    DATA data;
    struct _NODE *link;
}NODE;

typedef struct _HEAD {
    int count;
    struct _NODE *start;
    struct _NODE *end;
}HEAD;

HEAD* createQueue() {
    HEAD *queue = malloc(sizeof(HEAD));
    
    queue->count = 0;
    queue->start = NULL;
    queue->end = NULL;

    return queue;
}

void enqueue(HEAD *head, DATA data) {
    if (head->count >= MAX) {
        printf("queue is full\n");
        return;
    }

    NODE *newNode = malloc(sizeof(NODE));

    newNode->data = data;

    // 헤더의 맨 앞 부분 링크 수정
    newNode->link = head->start;
    head->start = newNode;

    // 헤더의 맨 뒤 부분 링크가 비어있는 경우,
    // 새로 추가된 노드의 링크로 지정
    if (head->end == NULL) {
        head->end = newNode;
    }
    
    head->count++;

    return;
}

DATA dequeue(HEAD *head) {
    if (head->end != NULL) {
        DATA returnData = head->end->data;

        // 경로 수정
        NODE *pre = head->start;
        while (pre->link != head->end) {
            pre = pre->link;
        }
        pre->link = NULL;

        // 맨 마지막 노드 해제 후 경로 재지정
        free(head->end);
        head->end = pre;

        head->count--;

        // 해제한 노드의 데이터 반환
        return returnData;
    }
}

DATA queueFront(HEAD *head) {
    if (head->count > 0)
        return head->start->data;
}

DATA queueRear(HEAD *head) {
    if (head->count > 0)
        return head->end->data;
}

bool emptyQueue(HEAD *head) {
    if (head->count <= 0) {
        return true;
    } else {
        return false;
    }
}

bool fullQueue(HEAD *head) {
    if (head->count >= MAX)
        return true;
    else
        return false;
}

int countQueue(HEAD *head) {
    return head->count;
}

void freeQueue(HEAD *head) {
    NODE *temp = head->start;

    while (temp != NULL) {
        temp = temp->link;
        free(head->start);
        head->start = temp;
        head->count--;
    }

    head->end = head->start;
    free(head);

    return;
}

int main() {
    
    HEAD *queue = createQueue();

    DATA data1 = {10, "Kim"};
    DATA data2 = {35, "Baek"};
    DATA data3 = {23, "Han"};
    DATA data4 = {44, "Choi"};
    DATA data5 = {55, "Lee"};
    DATA data6 = {77, "Park"};

    enqueue(queue, data1);
    enqueue(queue, data2);
    enqueue(queue, data3);
    enqueue(queue, data4);
    enqueue(queue, data5);

    DATA retrieved = queueRear(queue);
    printf("Age: %d, Name: %s\n", retrieved.age, retrieved.name);    

    printf("current count: %d\n", queue->count);

    retrieved = dequeue(queue);
    printf("Age: %d, Name: %s\n", retrieved.age, retrieved.name);    

    freeQueue(queue);

    return 0;
}