#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* link;
}NODE;

typedef struct Head {
    NODE* link;
}HEAD;

HEAD* createLinkedList() {
    HEAD *head = (HEAD *)malloc(sizeof(HEAD));
    head->link = NULL;
    return head;
}

void insertFirstNode(HEAD *head, int data) {
    if (head == NULL) {
        printf("This linked list does not exist");
        return;
    }
    // if no node exists in the linked list, insert first node
    if (head->link == NULL) {
        NODE* newNode = (NODE *)malloc(sizeof(NODE));
        newNode->data = data;
        newNode->link = NULL;
        head->link = newNode;
    }
}

void insertLastNode(HEAD *head, int data) {
    if (head == NULL) {
        printf("This linked list does not exist");
        return;
    }
    if (head->link == NULL) {
        insertFirstNode(head, data);
        return;
    }
    NODE *prev = head->link;
    prev->link = head->link->link;
    while (prev->link != NULL) { // 원래 마지막 노드 위치 탐색
        prev = prev->link;
    }
    // 새 노드 생성하고, 원래 마지막 노드의 바로 뒤에 연결
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->link = NULL;
    prev->link = newNode;
}

NODE* searchNode(HEAD *head, int searchData) {
    NODE *temp = head->link;
    while (temp != NULL) {
        if (temp->data == searchData) {
            return temp;
        } else {
            temp = temp->link;
        }
    }
    if (temp == NULL) {
        return NULL;
    }
}

void insertMiddleNode(HEAD *head, int pivot, int data) {
    NODE *prev = searchNode(head, pivot);
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->link = prev->link;
    prev->link = newNode;
}

void printList(HEAD *head) {
    NODE *temp = head->link;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
}

void freeLinkedList(HEAD *head) {
    NODE *temp = head->link;
    while (temp->link != NULL) {   // (조건) temp의 그 다음 노드가 (두 번째 노드) 있는지 판단
        head->link = temp->link; // 1. head가 가리키는 노드를 뒷쪽 노드 (두 번째 노드)로 변경
        free(temp);             // 2. temp가 가리키는 노드 (첫 번째 노드) 해체
        temp = head->link;      // 3. temp가 가리키는 노드를 head가 가리키는 노드 (두 번째 노드)로 변경
    }
    free(head);
}

int main() {
    HEAD* head = createLinkedList();
    insertFirstNode(head, 10);
    insertLastNode(head, 30);
    insertMiddleNode(head, 10, 20);
    insertMiddleNode(head, 10, 40);
    printList(head);
    freeLinkedList(head);
}