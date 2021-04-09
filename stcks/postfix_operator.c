#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 2
#define MAX_STRING_SIZE 100

int getAmount(FILE *fp);

int main() {
    FILE *fp = fopen("data_structure_and_algorithm/stcks/input_ex.txt", "r");
    FILE *fp2 = fopen("data_structure_and_algorithm/stcks/output.txt", "w");

    int amount = getAmount(fp);
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    char *str = malloc(sizeof(char) * MAX_STRING_SIZE);

    memset(buffer, 0, BUFFER_SIZE);
    memset(str, 0, MAX_STRING_SIZE);

    printf("%d\n", amount); // debug

    while (amount > 0) {
        amount--;

        while (strcmp(buffer, "\n") != 0) {
            fread(buffer, sizeof(char), 1, fp);

            if (strcmp(buffer, "\n") != 0)
                strcat(str, buffer);
        }
        
        printf("%s\n", str);

        memset(buffer, 0, BUFFER_SIZE);
        memset(str, 0, MAX_STRING_SIZE);

    }

    free(str); free(buffer);
    fclose(fp2); fclose(fp);

    return 0;
}

int getAmount(FILE *fp) {

    int amount = 0;

    char *buffer = malloc(sizeof(char) * 2);
    char *str = malloc(sizeof(char) * 20);
    
    while (strcmp(buffer, "\n") != 0) {
        fread(buffer, sizeof(char), 1, fp);
        strcat(str, buffer);
    }

    amount = atoi(str);
    
    free(str); free(buffer);

    return amount;
}