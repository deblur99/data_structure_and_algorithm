#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char data;
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

void pushStack(HEAD *head, char data) {

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

    char tempData = head->link->data;
    NODE *tempLink;

    if (head->link->link == NULL) {
        free(head->link);
        head->link = NULL;
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

    FILE *fp = fopen("data_structure_and_algorithm/stcks/output.txt", "w");

    char input[6] = "A+B*C";
    char output[6] = {0, };
    
    char outputLetter;
    int i, j;

    HEAD *head = createStack();

    for (i = 0, j = 0; i < strlen(input); i++) {

        if (head->link == NULL) {

            // 스택에 아무것도 없을때 연산자를 스택에 push
            if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
                pushStack(head, input[i]);
                continue;
            }   
            
            // 현재 값이 연산자가 아닐때 output에 저장
            else {
                output[strlen(output)] = input[i];
                continue;
            }
                
        } else {

            if (head->link->data == '+' || head->link->data == '-') {
            // 스택에 연산자가 있을때 현재 값이 *, /일 경우 push 연산
                if (input[i] == '*' || input[i] == '/') {
                    pushStack(head, input[i]);
                    continue;
                }

            // 스택에 연산자가 있을때 현재 값이 +, -일 경우 스택 pop 연산 후 현재 값 push 연산
                else if (input[i] == '+' || input[i] == '-') {

                    j = strlen(output);

                    while (head->link == NULL) {
                        outputLetter = popStack(head);
                        output[j] = outputLetter;
                        j++;
                    }

                    pushStack(head, input[i]);

                    continue;
                }
            // 스택에 연산자가 있을때 현재 값이 연산자가 아닐 경우 아웃풋에 추가
                else {
                    output[strlen(output)] = input[i];
                    continue;
                }
            }
        }

        if (!(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'))
            // 현재 값이 연산자가 아닐 경우 아웃풋에 추가
            output[strlen(output)] = input[i];
    }

    i = strlen(output);

    while (head->link != NULL) {
        outputLetter = popStack(head);
        output[i] = outputLetter;
        i++;
    }
    
    fwrite(output, sizeof(char), strlen(output), fp);
    fclose(fp);

    return 0;
}