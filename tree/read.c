#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer = malloc(sizeof(char) * 10);
    FILE *fp = fopen("data_structure_and_algorithm/tree/input.txt", "r");

    for (int i = 0; i < 10; i++) {
        fscanf(fp, "%s", buffer);
        printf("%s ", buffer);
    }

    fclose(fp);
    free(buffer);
}