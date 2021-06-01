#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int visited[MAX];

int stack[MAX];

int prevList[MAX];  // 스택에서 pop 연산되어 반환된 값을 저장하는 배열

int top = -1;

void init() {
    top = -1;
    for (int i = 0; i < MAX; i++) {
        stack[i] = -1;
        visited[i] = 0;
        prevList[i] = -1;
    }
}

void push(int index) {
    if (top >= MAX)
        return;
    
    stack[++top] = index;
    return;
}

int pop() {
    if (top <= -1)
        return -1;
    
    else
        return stack[top--];
}

int isEmpty() {
    if (top <= -1)
        return 1;
    
    else return 0;
}

int getValue(FILE *fp) {
    int result = -1;
    fscanf(fp, "%d", &result);
    return result;
}

int findCycleByDFS(int **graph, int size, int init) {
    int isConnected = 0, idxPrev = -1, result = 0;

    // 최초로 탐색할 정점에 인접한 정점이 없을 경우, 다음 값을 init으로 대체한다.
    while (!isConnected) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (graph[i][j] == 1) {
                    init = i;
                    isConnected = 1;
                    break;
                }
            }

            if (isConnected)
                break;

            // 연결된 정점이 없는 경우, 0을 반환        
            if (i == size - 1)
                return 0;
        }
    }

    // 최초로 탐색할 정점을 스택에 저장
    push(init);

    // 스택이 비어 있을 때까지 반복
    while (!isEmpty()) {
        int idx = pop();
        prevList[++idxPrev] = idx;

        if (visited[idx] == 0) {
            visited[idx] = 1;
        }

        for (int i = size - 1; i >= 0; i--) {

            if (graph[idx][i] == 1) {
                if (visited[i] == 0)
                    push(i);
                
                else {
                    for (int j = idxPrev; j >= 0; j--) {
                        if (i == prevList[j] && i - j > 1) {
                            result++;
                        }
                    }
                }
            }
        }
    }

    return result;
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

        // find cycle in the graph
        init();
        result = findCycleByDFS(graph, sizeOfGraph, 0);

        // save results into output.txt
        fprintf(fp2, "%d\n", result);

        // free allocated memory
        for (int j = 0; j < sizeOfGraph; j++) {
            free(graph[j]);
        }

        free(graph);
    }
}