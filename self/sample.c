#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Process {
    char operate[10];
    char element[50];
}process;

int getSizeFromFile(FILE *fp) {
    int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return size;
}

char* readFile(FILE *fp, int size) {
    char *buffer = (char *)malloc(sizeof(char));
    char *expression_raw = (char *)malloc(sizeof(char) * size);
    memset(expression_raw, 0, size);

    // read input.txt and save item to token
    int i = 0;
    while (!feof(fp) && (i < size)) {
        fread(buffer, sizeof(char), 1, fp);
        expression_raw[i] = buffer[0];
        i++;
    }

    free(buffer);

    return expression_raw;
}

// find count of statements
int getCountOfStatements(char* expression) {

    int count = 0;
    char *tok = strtok(expression, "\r\n");
    count = atoi(tok);
    return count;
}

// capsulize each statement
void capsulize(char* expression, process *result) {

    int index = 0, j = 0;
    char *statement[3] = {"Evaluate", "Swap", "Count"};

    char *tok = strtok(expression, "\r\n");
    tok = strtok(NULL, "\n");

    while (tok != NULL) {
        if (strcmp(tok, "Evaluate") == 0 || strcmp(tok, "Swap") == 0 || strcmp(tok, "Count") == 0) {
            strcpy((result + index)->operate, tok);
            tok = strtok(NULL, " ");
        } else {
            tok = strtok(NULL, "\r\n");
            strcpy((result + index)->element, tok);
            index++;
            tok = strtok(NULL, "\n");
        }
    }

    for (int i = 0; i < 3; i++) {
        printf("%s ", (result+i)->operate);
        printf("%s\n", (result+i)->element);
    }

    return;
}

int main() {

    FILE *fp = fopen("data_structure_and_algorithm/input.txt", "r");
    FILE *fp2 = fopen("data_structure_and_algorithm/output.txt", "w");

    // get entire size and count expressions in input.txt
    int size = getSizeFromFile(fp);

    char *expression_raw = readFile(fp, size);
    char *temp = malloc(sizeof(strlen(expression_raw)));
    strcpy(temp, expression_raw);
    
    int count = getCountOfStatements(expression_raw);
    strcpy(expression_raw, temp);
    free(temp);

    process items[count];

    capsulize(expression_raw, items);

    printf("%s ", items->element);

    fclose(fp2);
    fclose(fp);
    
    free(expression_raw);

    return 0;
}