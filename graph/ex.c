#include <stdio.h>
#include <stdlib.h>

int main() {
    int **graph = malloc(sizeof(int *) * 5);
    for (int j = 0; j < 5; j++) {
        graph[j] = malloc(sizeof(int) * 5);
    }

    graph[0][0] = 10;
    
    printf("%d\n", graph[0][0]);

    for (int i = 0; i < 5; i++)
        free(graph[i]);

    free(graph);

    return 0;
}