#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 12
#define ARR_SIZE 100
#define BUFFER_SIZE 10

typedef struct _TYPE {
    int seek;
    int location;
}TYPE;

typedef struct _NODE {
    int data;
    int valid;
    struct _NODE *left;
    struct _NODE *right;
}NODE;

NODE tree[ARR_SIZE];

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

TYPE getType(FILE *fp) {
    TYPE result = {0, -1};
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

    // initialize int type variables
    int amountOfTrees = getAmountofTrees(fp);
    int amountOfNodes = 0, element = 0;


    for (int i = 0; i < amountOfTrees; i++) {  // get amount of Nodes and type of processing
        amountOfNodes = getAmountofNodes(fp);
        processType = getType(fp);  // this can be 0 or 1. 0 means dfs, 1 means bfs.
        printf("\n%d %d\n", processType.seek, processType.location);
        // init the tree
        init();

        // iterate like the number of nodes
        for (int j = 0; j < amountOfNodes; j++) {
            element = getData(fp);
            addNode(0, element);
        }

        // debug
        printTree(0);
        printf("\n");
    }

    fclose(fp2);
    fclose(fp);
}