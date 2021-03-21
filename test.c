#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = fopen("data_structure_and_algorithm/test.txt", "r");
    char *buffer = malloc(sizeof(char));

    while (!feof(fp)) {
        fread(buffer, sizeof(char), 1, fp);
        if (!strcmp(buffer, " ") || !strcmp(buffer, "\r") || !strcmp(buffer, "\n"))
            fgets(buffer, 1, fp);
        else
            printf("%d ", atoi(buffer));
    }

    free(buffer);
    fclose(fp);

    return 0;
}