#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARR_SIZE 100
#define BUFFER_SIZE 10

typedef enum _TYPE {
    DFS = 0, BFS
}TYPE;

typedef struct _INFO {
    int seek;
    int location;
}INFO;

typedef struct _NODE {
    int data;
    int valid;
    struct _NODE *left;
    struct _NODE *right;
}NODE;

NODE tree[ARR_SIZE];    // declare BST
int dfs_index;

NODE *queue[ARR_SIZE];  // declare queue for BFS
int front, rear;

// functions which handle the tree
void init() {
    for (int i = 0; i < ARR_SIZE; i++) {
        tree[i].data = -1;
        tree[i].valid = 0;
        tree[i].left = tree[i].right = NULL;
    }
    return;
}

void addNode(int index, int data) {
    // base case
    if (tree[index].valid == 0) {
        tree[index].data = data;
        tree[index].valid = 1;

        if (index == 0) return;

        int parentIndex = (index - 1) / 2;
        
        if (index % 2 == 0) // if added node locates right subtree of parent
            tree[parentIndex].right = &tree[index];
        else
            tree[parentIndex].left = &tree[index];

        return;
    }

    // general case
    if (data < tree[index].data) {
        addNode(index * 2 + 1, data);   // go left
    } else {
        addNode(index * 2 + 2, data);   // go right
    }

    return;
}

void printTree(int index) {
    // base case
    if (tree[index].valid == 0) {
        return;
    }

    printf("%d ", tree[index].data);

    // general case
    if (tree[index].right != NULL) {
        if (tree[index].left != NULL) {
            printTree(index * 2 + 1);
            printTree(index * 2 + 2);
        } else {
            printTree(index * 2 + 2);
        }
    } else {
        if (tree[index].left != NULL)
            printTree(index * 2 + 1);
    }
}

// using preorder method
int dfs(int index, int target) {
    // 호출할 때마다 dfs_index 전역 변수를 1 증가시킨다.
    // 좌측 탐색 + 우측 탐색 순으로 재귀호출하여 좌측이 우선적으로
    // 탐색되어야 정확하게 구할 수 있다.
    // 또한, 정수값을 반환해야 하므로, 각 호출은 return문으로 이루어져야 한다.
    // case 1) 좌측, 우측 서브트리가 비어있지 않을 경우: 좌측 -> 우측 순으로 탐색
    // case 2) 좌측 서브트리만 비어있지 않을 경우: 좌측만 탐색
    // case 3) 우측 서브트리만 비어있지 않을 경우: 우측만 탐색
    dfs_index++;

    // base case
    if (dfs_index == target) {
        return tree[index].data;
    }

    if (tree[index].valid != 0) {
        // general case
        if (tree[index].left != NULL) {
            if (tree[index].right != NULL)
                return dfs(index * 2 + 1, target) + dfs(index * 2 + 2, target); 
            else
                return dfs(index * 2 + 1, target);
        }

        else {
            if (tree[index].right != NULL)
                return dfs(index * 2 + 2, target);
        }
    }
}

// functions of handling queue for bfs
void initQueue() {
    for (int i = 0; i < ARR_SIZE; i++) {
        queue[i] = NULL;
    }
    front = rear = -1;
}

void enqueue(NODE *node) {
    queue[++rear] = node;
    if (front == -1) front++;
}

NODE* dequeue() {
    NODE *node = queue[front];
    if (front == rear)
        front = rear = -1;
    else front++;
    return node;
}

int isEmpty() {
    if (front == rear == -1) return 1;
    return 0;
}

int bfs(int bfs_index, int target) {
    if (bfs_index == target == 1)
        return tree[0].data;

    NODE *currentNode = &tree[0];   // initialization
    initQueue();
    while (currentNode != NULL) {
        if (currentNode->left != NULL)
            enqueue(currentNode->left);
        
        if (currentNode->right != NULL)
            enqueue(currentNode->right);
        
        if (isEmpty())
            currentNode = NULL;
        
        else {
            bfs_index++;
            currentNode = dequeue();

            if (bfs_index == target)
                return currentNode->data;
        }
    }
} 

// parsing functions
int getAmountofTrees(FILE *fp) {
    char *buffer = malloc(BUFFER_SIZE);
    int amountOfTrees = 0;

    // get amount of trees from txt
    fscanf(fp, "%d", &amountOfTrees);

    free(buffer);

    return amountOfTrees;
}

int getAmountofNodes(FILE *fp) {
    int num; fscanf(fp, "%d", &num);
    return num;
}

INFO getInfo(FILE *fp) {
    INFO result = {0, -1};
    int isEqual = 0, index = 0;
    char key[3] = {'\n', };
    char buffer[BUFFER_SIZE];
    char type_arr[2][4] = {"dfs", "bfs"};

    fscanf(fp, "%s", buffer);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (buffer[j] != type_arr[i][j]) {
                break;
            }
            else if (j == 2)
                isEqual = 1;
        }
        if (isEqual == 1) {
            result.seek = i;
            break;
        }
    }

    for (int i = 0; i < strlen(buffer); i++) {
        if (isdigit(buffer[i])) {
            key[index] = buffer[i];
            index++;
        }
    }

    result.location = atoi(key);

    return result;
}

int getData(FILE *fp) {
    int element;
    fscanf(fp, "%d", &element);
    return element;
}

int main() {
    FILE *fp = fopen("data_structure_and_algorithm/tree/input.txt", "r");
    FILE *fp2 = fopen("data_structure_and_algorithm/tree/output.txt", "w");

    TYPE processType;

    INFO processInfo;

    // initialize int type variables
    int amountOfTrees = getAmountofTrees(fp);
    int amountOfNodes = 0, element = 0, result = 0;


    for (int i = 0; i < amountOfTrees; i++) {  // get amount of Nodes and type of processing
        amountOfNodes = getAmountofNodes(fp);
        processInfo = getInfo(fp);      // processInfo.seek can be 0 or 1. 0 means dfs, 1 means bfs.
        processType = processInfo.seek; // mapping 0 to DFS, 1 to BFS

        // init the tree
        init();

        // iterate along the number of nodes
        for (int j = 0; j < amountOfNodes; j++) {
            element = getData(fp);
            addNode(0, element);
        }

        // search by DFS or BFS
        if (processType == DFS) {
            dfs_index = 0;
            result = dfs(0, processInfo.location);  
        }

        else if (processType == BFS)
            result = bfs(1, processInfo.location);

        // save the result into output
        fprintf(fp2, "%d\n", result);
    }

    fclose(fp2);
    fclose(fp);
}