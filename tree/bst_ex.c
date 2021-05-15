#include <stdio.h>
#define MAX 100

typedef struct _node {
    int valid;
    int data;
    struct _node* left;
    struct _node* right;
}NODE;

NODE tree[MAX];

void init() {
    for (int i = 0; i < MAX; i++) {
        tree[i].valid = 0;
        tree[i].data = -1;
        tree[i].left = tree[i].right = NULL;
    }

    return;
}

int isEmpty(int curIdx) {
    return tree[curIdx].valid == 0;
}

void add(int curIdx, int data) {
    if (isEmpty(curIdx)) {
        tree[curIdx].data = data;
        tree[curIdx].valid = 1;
        if (curIdx == 0) return;

        int parentIdx = (curIdx - 1) / 2;

        if (curIdx % 2 == 0) {  //right
            tree[parentIdx].right = &tree[curIdx];
        } else {
            tree[parentIdx].left = &tree[curIdx];
        }

        return;
    }

    if (data < tree[curIdx].data) {
        add(curIdx * 2 + 1, data);  // go left
    } else {
        add(curIdx * 2 + 2, data);  // go right
    }

    return;
}

int largest(int curIdx) {   // return the idx of largest node
    if (tree[curIdx].right == NULL && tree[curIdx].valid == 1)
        return curIdx;
    if (tree[curIdx].right != NULL)
        return largest(curIdx * 2 + 2); // go right;
}

void del(int curIdx, int target) {
    // 1. go to the target node
    // 2-1. case1
    // 2-2. case2
    // 2-3. case3
    // 2-4. case4

    if (tree[curIdx].valid == 0)
        return;

    // base case
    int parentIdx = (curIdx - 1) / 2;
    if (tree[curIdx].data == target) {
        tree[curIdx].valid = 0;


        // case 1
        if (tree[curIdx].left == NULL && tree[curIdx].right == NULL) {
            if (curIdx % 2 == 0) {
                tree[parentIdx].right = NULL;
            } else {
                tree[parentIdx].left = NULL;
            }
        }

        // case 2
        else if (tree[curIdx].left == NULL && tree[curIdx].right != NULL) {
            if (curIdx % 2 == 0) {
                tree[parentIdx].right = &tree[curIdx * 2 + 2];  // right subtree is attached to the parent
            }
            else {
                tree[parentIdx].left = &tree[curIdx * 2 + 2];
            }
        }

        // case 3
        else if (tree[curIdx].left == NULL && tree[curIdx].right != NULL) {
            if (curIdx % 2 == 0) {  // right
                tree[parentIdx].right = &tree[curIdx * 2 + 1];  // left subtree is attached to the parent
            }
            else {
                tree[parentIdx].left = &tree[curIdx * 2 + 1];
            }
        }
        
        // case 4
        else {
            int idx_largest = largest(curIdx * 2 + 1);
            tree[curIdx].data = tree[idx_largest].data;
            tree[curIdx].valid = 1;

            if (curIdx % 2 == 0) {  // right
                tree[(idx_largest - 1) / 2].right = NULL;
            }
            else {
                tree[(idx_largest - 1) / 2].left = NULL;
            }
        }
        return;
    }

    // general case
    if (target < tree[curIdx].data) {
        del(curIdx * 2 + 1, target);
    } else {
        del(curIdx * 2 + 2, target);
    }
}

void print(int curIdx) {
    if (tree[curIdx].valid == 0)
        return;
    
    else {
        printf("%d ", tree[curIdx].data);
        if (tree[curIdx].left != NULL) {
            if (tree[curIdx].right != NULL) {
                print(curIdx * 2 + 1);
                print(curIdx * 2 + 2);
            }
            else
                print(curIdx * 2 + 1);
        }

        else if (tree[curIdx].right != NULL) {
            if (tree[curIdx].left != NULL) {
                print(curIdx * 2 + 1);
                print(curIdx * 2 + 2);
            } else {
                print(curIdx * 2 + 2);
            }
        }
    }

    return;
}

int main() {
    init();

    add(0, 23);
    add(0, 18);
    add(0, 44);
    add(0, 12);
    add(0, 20); 
    add(0, 35);
    add(0, 52);
    add(0, 18);
    del(0, 44);

    print(0);

    return 0;   
}