#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    char data;
    struct ListNode *link;
}listNode;

typedef struct {
    listNode *head;
}linkedList_h;

linkedList_h* createLinkedList_h() {
    linkedList_h *CL;
    CL = (linkedList_h *)malloc(sizeof(linkedList_h));
    CL->head = NULL;
    return CL;
}

void printList(linkedList_h *CL) {
    listNode *p;
    printf("CL = (");
    p = CL->head;
    do {
        printf("%c", p->data);
        p = p->link;
        if (p != CL->head) printf(", ");
    } while (p != CL->head);
    printf(") \n");
}

void freeLinkedList(linkedList_h *CL) {
    listNode *p;
    if (CL->head == NULL) return;
    if (CL->head == CL->head->link) {
        free(CL->head);
        CL->head = NULL;
        return;
    } else {
        p = CL->head;
        do {
            p->link = p->link->link;
            free(p);
        } while (p != CL->head);
    }
}

// 첫 번째 노드 삽입 연산 (헤더 위치 바꿈)
void insertFirstNode(linkedList_h *CL, int x) {
    listNode *newNode, *temp;
    newNode = (listNode *)malloc(sizeof(listNode));
    newNode->data = x;
    if (CL->head == NULL) {
        CL->head = newNode;
        newNode->link = newNode;
    } else {
        temp = CL->head;
        while (temp->link != CL->head)
            temp = temp->link;      // temp 노드가 새로 삽입할 노드의 선행자 노드가 될 때까지 연결리스트 순회
        newNode->link = temp->link; // 새로 삽입할 노드의 링크 필드에 기존의 선행자 노드 링크를 저장
        temp->link = newNode;       // temp 노드의 링크 필드에 새로 삽입할 노드의 주소 저장 
        CL->head = newNode;         // 연결리스트 헤더의 위치 갱신 (pre -> newNode)
        // (temp -> newNode -> (newNode->link))
    }
}

// 선행자 노드 뒤에 노드 삽입하는 연산
void insertMiddleNode(linkedList_h *CL, listNode *pre, int x) {
    listNode *newNode = (listNode *)malloc(sizeof(listNode));
    newNode->data = x;
    if (CL == NULL) {
        CL->head = newNode;
        newNode->link = newNode;
    } else {
        newNode->link = pre->link;
        pre->link = newNode;
    }
}

// 노드 삭제 연산 : CL에서 따지고, old에서 따지고고
void deleteNode(linkedList_h *CL, listNode *old) {
    listNode *pre;
    // 연결리스트가 비어 있으면 함수 종료
    if (CL->head == NULL) return;
    // 연결리스트에 노드가 하나밖에 없으면 해제 후 함수 종료
    if (CL->head->link == CL->head) {
        free(CL->head);
        CL->head = NULL;
        return;
    } else if (old == NULL) return; // 삭제할 노드가 없는 경우 함수 종료
    else {
        pre = CL->head;
        while (pre->link != old) {  // 선행자 노드 탐색: 삭제할 노드 바로 앞에 있는 노드 찾기
            pre = pre->link;
        }
        pre->link = old->link;      // 삭제 연산 수행
        if (old == CL->head) CL->head = old->link;
        free(old);
    }
}

listNode* searchNode(linkedList_h *CL, int data) {
    listNode *temp;
    temp = CL->head;
    if (temp == NULL) return NULL;
    do {
        if (temp->data == data) return temp;
        else temp = temp->link;
    } while (temp != CL->head); // do while문을 씀으로써 맨 처음에 while문을 만족하지 않을 때,
    return NULL;                // 탐색 연산을 예외적으로 수행할 수 있음
}

int main() {
    linkedList_h *CL;
    listNode *p;
    CL = createLinkedList_h();
    printf("(1) 원형 연결 리스트 생성하기!\n");
    getchar();

    printf("(2) 원형 연결 리스트에 'A' 추가하기!\n");
    insertFirstNode(CL, 65);
    printList(CL); getchar();

    printf("(3) 원형 연결 리스트에서 'A' 뒤에 'B' 추가하기!\n");
    p = searchNode(CL, 'A'); insertMiddleNode(CL, p, 66);
    printList(CL); getchar();

    printf("(4) 원형 연결 리스트에서 'B' 뒤에 'C' 추가하기!\n");
    p = searchNode(CL, 'B'); insertMiddleNode(CL, p, 67);
    printList(CL); getchar();

    printf("(5) 원형 연결 리스트에서 'B' 삭제하기!\n");
    p = searchNode(CL, 'B'); deleteNode(CL, p);
    printList(CL); getchar();

    freeLinkedList(CL);

    return 0;
}