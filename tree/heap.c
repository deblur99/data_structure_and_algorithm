// AVL: balanced tree인지 항상 확인
#include <stdio.h>
#define MAX 100

typedef struct _NODE {
    int data;   //key
    struct _NODE *left;
    struct _NODE *right;
}NODE;

NODE heap[MAX];
int idxLast;    // last element index

void init() {
    for (int i = 0; i < MAX; i++) {
        heap[i].data = -1;
        heap[i].left = heap[i].right = NULL;
    }

    idxLast = -1;
}

void swap(int idxA, int idxB) {
    int tmp = heap[idxA].data;
    heap[idxA].data = heap[idxB].data;
    heap[idxB].data = tmp;
}

void reheapup(int idxNewNode) {
    if (idxNewNode != 0) {
        int idxParent = (idxNewNode - 1) / 2;
        if (heap[idxNewNode].data > heap[idxParent].data) {
            swap(idxNewNode,idxParent);
            reheapup(idxParent);
        }
    }
}

void reheapdown(int idxRoot) {
    if (heap[idxRoot].left != NULL) {
        int *leftKey = &heap[idxRoot].left->data;
        int *rightKey = NULL;

        if (heap[idxRoot].right != NULL) {
            rightKey = &heap[idxRoot].right->data;
        }

        int idxLarger;

        if (rightKey == NULL || *leftKey > *rightKey) {
            idxLarger = idxRoot * 2 + 1;
        }

        else {
            idxLarger = idxRoot * 2 + 2;
        }

        if (heap[idxRoot].data < heap[idxLarger].data) {
            swap(idxRoot,idxLarger);
            reheapdown(idxLarger);
        }
    }
}

void add(int data) {
    heap[++idxLast].data = data;

    if (idxLast % 2 == 0) { // right child
        heap[(idxLast - 1) / 2].right = &heap[idxLast];
    }

    else {
        heap[(idxLast - 1) / 2].left = &heap[idxLast];
    }

    reheapup(idxLast);
}

int del() {
    int ret = heap[0].data;

    heap[0].data = heap[idxLast].data;

    if (idxLast % 2 == 0) { // right child
        heap[(idxLast - 1) / 2].right = NULL;
    }

    else {
        heap[(idxLast - 1) / 2].left = NULL;
    }

    idxLast--;
    reheapdown(0);

    return ret;
}

int main() {
    init();

    add(78);
    add(56);
    add(32);
    add(45);
    add(8);
    add(23);
    add(19);

    for (int i = 0; i < 3; i++) {
        printf("%d ", del());
    }

    return 0;
}