#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct Data {
    int age;
    char name[10];
}DATA;

DATA stack[MAX];

int top = -1; // -1은 스택이 비었음을 의미

void create() {

    for (int i = 0; i < MAX; i++) {
        stack[i].age = 0;
        memset(stack[i].name, 0, strlen(stack[i].name));
    }

    top = -1;
}

void push(DATA input) {

    if (top >= MAX) {
        printf("stack is full\n");
        return;
    }

    else if (top < -1) {
        printf("stack has problem\n");
        return;
    }

    else {
        stack[++top] = input;
        return;
    }
}

DATA pop() {
    if (top > -1) {
        return stack[top--];
    }
}

DATA getTop() {

    if (top > -1) {
        return stack[top];
    }
}

int main() {
    DATA data1, data2;

    strcpy(data1.name, "Park");
    data1.age = 24;

    strcpy(data2.name, "Kim");
    data2.age = 45;

    push(data1);
    push(data2);

    DATA temp = getTop();

    printf("%s %d\n", temp.name, temp.age);
    /*
    for (int i = 0; i < 2; i++) {
        temp = pop();
        printf("Name: %s, Age: %d\n", temp.name, temp.age);
    }*/

    return 0;
}