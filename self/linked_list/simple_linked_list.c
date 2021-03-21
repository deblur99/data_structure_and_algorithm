#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체 선언
typedef struct ListNode {
    char data[4];
    struct ListNode* link;
}listNode;

// 연결리스트 헤더 부분 선언
typedef struct {
    listNode* head; // listNode*형 변수 head는 노드 구조체를 가리키는 linkedList_h의 멤버
}linkedList_h;

// 빈 리스트 생성하여 반환
linkedList_h* createLinkedList_h() 
    linkedList_h* L = (linkedList_h *)malloc(sizeof(linkedList_h));
    L->head = NULL;
    return L;
}

void freeLinkedList_h(linkedList_h* L) {
    listNode* p;
    while (L->head != NULL) {
        p = L->head;
        L->head = L->head->link;
        free(p);
        p = NULL;
    }
}

void printList(linkedList_h* L) {
    listNode* p;
    printf("L = (");
    p = L->head;
    while (p != NULL) {
        printf("%s", p->data);
        p = p->link;
        if (p != NULL) printf(", ");
    }
    printf(")\n");
}

listNode* getNode(char *string) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    strcpy(newNode->data, string);
    return newNode;
}

// Inserting Node
void insertFirstNode(linkedList_h* L, char *string) {
    listNode* newNode = getNode(string);
    newNode->link = L->head;
    L->head = newNode;
}

void insertMiddleNode(linkedList_h* L, listNode* pre, char* string) {
    listNode* newNode = getNode(string);
    if (L == NULL) {
        newNode->link = NULL;
        L->head = newNode;
    } else if (pre == NULL) {
        L->head = newNode;
    } else {
        newNode->link = pre->link;
        pre->link = newNode;
    }
}

void insertLastNode(linkedList_h* L, char *string) {
    listNode* newNode = getNode(string);
    listNode* temp;
    newNode->link = NULL;
    if (L == NULL) {
        L->head = newNode;
        return;
    }
    temp = L->head;
    while (temp->link != NULL) temp = temp->link;
    temp->link = newNode;
}

void deleteNode(linkedList_h* L, listNode* p) {
    listNode* pre;
    if (L->head == NULL) return;
    if (L->head->link == NULL) { // if the linked list has only one node:
        free(L->head);          // free remaining the node
        L->head = NULL;
        return;
    }
    else if (p == NULL) return;
    else {
        pre = L->head;
        while (pre->link != p) {
            pre = pre->link;
        }
        pre->link = p->link;
        free(p);
    }
}

listNode* searchNode(linkedList_h* L, char* string) {
    listNode* temp;
    temp = L->head;
    while (temp != NULL) {
        if (strcmp(temp->data, string) == 0) return temp;
        else temp = temp->link;
    }
    return temp;
}

void reverse(linkedList_h* L) {
    listNode* p;
    listNode* q;
    listNode* r;

    p = L->head;
    q = NULL;
    r = NULL;

    while (p != NULL) {
        r = q;
        q = p;
        p = p->link;
        q->link = r;
    }
    L->head = q;
}

int main() {
    linkedList_h *L;
    listNode *p;

    printf("1) 공백 리스트 생성하기\n");
    L = createLinkedList_h();
    printList(L); getchar();

    printf("2) 리스트에 [Jan] 노드 삽입하기\n");
    insertFirstNode(L, "Jan");
    printList(L); getchar();

    printf("3) 리스트 처음에 [Feb] 노드 삽입하기\n");
    insertFirstNode(L, "Feb");
    printList(L); getchar();

    printf("4) 리스트 마지막에 [Dec] 노드 삽입하기\n");
    insertLastNode(L, "Dec");
    printList(L); getchar();

    printf("5) [Jan] 노드 삭제하기\n");
    p = searchNode(L, "Jan");
    deleteNode(L, p);
    printList(L); getchar();

    printf("6) 리스트 중간에 [Oct] 노드 삽입하기\n");
    p = searchNode(L, "Feb");
    insertMiddleNode(L, p, "Oct");
    printList(L); getchar();

    printf("7) 연결 리스트의 역순 바꾸기\n");
    reverse(L);
    printList(L); getchar();

    printf("8) 리스트 공간을 해제하여 공백 리스트로 만들기\n");
    freeLinkedList_h(L);
    printList(L); getchar();

    return 0;
}