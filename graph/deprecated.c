#include <stdio.h>
#include <stdlib.h>

typedef struct _HEAD {
    struct _VRTX *head;
}HEAD;

typedef struct _VRTX {
    int *info;
    struct _VRTX *edge;
    struct _VRTX *path;
}VRTX;

HEAD* createList() {
    HEAD *list = malloc(sizeof(HEAD));
    list->head = NULL;
    return list;
}

void insertVertex(HEAD *list, int *arr) {
    VRTX *newVertex = malloc(sizeof(VRTX));
    newVertex->info = arr;
    newVertex->path = NULL;

    if (list->head == NULL) {   // if list is empty
        list->head = newVertex;
        newVertex->edge = NULL;
    }

    else {  // if list has at least one node
        VRTX *place = list->head;

        while (place->edge != NULL) {
            place = place->edge;
        }

        place->edge = newVertex;
        newVertex->edge = NULL;
    }

    return;
}

void connectEdge(HEAD *list, int size) {
    if (list->head == NULL) // if the list is empty
        return;
    
    VRTX *current = list->head;
    VRTX *connect = list->head;

    for (int i = 0; i < size; i++) {

        if (i >= 1) {
            current = current->edge;
        }

        // find 1 in the row
        for (int j = 0; j < size; j++) {

            if (current->info[j] == 1) {
                
                for (int k = ; k < size; k++) {
                    connect = connect->edge;
                }
                
                while (current->path != NULL) {
                    current = current->path;
                }

                current->path = connect;
            }
        }
    }

    return;
    /*
    // connect vertices
    for (int i = 0; i < size; i++) {
        // init
        seek = -1;
        connect = list->head;

        if (i >= 1)
            current = current->edge;

        // 1이라고 적혀 있는 자리에 대응하는 vertex를 현재 vertex에 연결
        for (int j = 0; j < size; j++) {
            seek++;

            if (current->info[j] == 1) {
                for (int k = 0; k < seek; k++) {
                    connect = connect->edge;
                }
                
                while (current->path != NULL) {
                    current = current->path;
                }

                current = connect;
            }
        }
    }
    */
}

void freeList(HEAD *list) {
    VRTX *temp = list->head;
    if (temp == NULL) {
        free(list);
        return;
    }

    // 위의 식을 통과했으나 첫 번째 노드의 다음 노드가 없을 경우가 있으므로
    // 최소 1회 이상 처리해야 한다. (do-while문)
    do {
        list->head = temp->edge;
        free(temp);
        temp = list->head;    
    }
    while (temp->edge != NULL);

    free(list);
    return;
}

//debug
void printList(HEAD *list) {
    VRTX *temp = list->head;
    int n = 0;
    while (temp != NULL) {
        n++;
        temp = temp->edge;
    }
    printf("Node : %d\n", n);
    return;
}

int getValue(FILE *fp) {
    int result = -1;
    fscanf(fp, "%d", &result);
    return result;
}

int findCycleByDFS(int **graph) {
    
    return 0;
}

int main() {
    int amountOfGraph = 0;
    int sizeOfGraph = 0, result;
    FILE *fp = fopen("data_structure_and_algorithm/graph/input.txt", "r");
    FILE *fp2 = fopen("data_structure_and_algorithm/graph/output.txt", "w");

    amountOfGraph = getValue(fp);

    // iterate and process for each graphs
    for (int i = 0; i < amountOfGraph; i++) {
        result = 0;
        sizeOfGraph = getValue(fp);

        // create a graph
        int **graph = malloc(sizeof(int *) * sizeOfGraph);

        for (int j = 0; j < sizeOfGraph; j++) {
            graph[j] = malloc(sizeof(int) * sizeOfGraph);
        }

        // get all of elements of the graph and make nodes
        for (int j = 0; j < sizeOfGraph; j++) {
            for (int k = 0; k < sizeOfGraph; k++) {
                graph[j][k] = getValue(fp);
            }
        }

        // create an adjacency list
        HEAD *list = createList();

        int *info = malloc(sizeof(int)*sizeOfGraph);
        
        for (int j = 0; j < sizeOfGraph; j++) {
            for (int k = 0; k < sizeOfGraph; k++) {
                info[k] = graph[j][k];
            }
            
            insertVertex(list, info);
        }

        //connectEdge(list, sizeOfGraph);

        printList(list);
        free(info);
        freeList(list);

        // find cycle in the graph
        result = findCycleByDFS(graph);

        // save results into output.txt
        fprintf(fp2, "%d\n", result);

        // free allocated memory
        for (int j = 0; j < sizeOfGraph; j++) {
            free(graph[j]);
        }

        free(graph);
    }
}