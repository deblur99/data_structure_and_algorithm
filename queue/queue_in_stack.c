#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 5

typedef struct _DATA {
    char *name;
    int age;
}DATA;

// 정적 자료구조는 기본적으로 전역변수 사용
DATA queue[MAX];
int front, rear;

void create() {
    for (int i = 0; i < MAX; i++) {
        queue[i].name = NULL;
        queue[i].age = 0;
    }
    front = rear = -1;
}

bool isEmpty() {
    if (front == -1 && rear == -1)
        return true;
    else
        return false;
}

bool isFull() {
    if ((front == 0 && rear == MAX - 1) ||
        (front == rear + 1)
        ) return true;
    else
        return false;
}

void enqueue(DATA data) {
    if (isFull) return;
    
    if (front == -1) front = 0;
    rear = (rear + 1) % MAX;
    queue[rear] = data;

    return;
}

DATA dequeue() {
    if (isEmpty()) return;
    DATA data = queue[front];
    if (front == rear) {
        front = rear = -1;
    }
    else {
        front = (front + 1) % MAX;
    }
    return data;
}

int main() {
    DATA data1, data2;

    data1.age = 10;
    strcpy(data1.name, "Park");

    data2.age = 20;
    strcpy(data2.name, "Kim");

    enqueue(data1);
    enqueue(data2);
    enqueue(data2);

    DATA temp = dequeue();

    printf("Name: %s, Age: %d\n", temp.name, temp.age);

    return 0;
}