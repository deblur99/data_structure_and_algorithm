#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct size {
    int row;
    int col;
}SIZE;

// find actual amount of mazes in the file
int findAmountMaze(FILE *fp) {

    int amount_mazes;
    char *buffer = (char *)malloc(sizeof(char));
    char buffer_amount_mazes[5];

    fread(buffer, sizeof(char), 1, fp); 
    strcpy(buffer_amount_mazes, buffer);

    while (strcmp(buffer, "\r") != 0) {
        fread(buffer, sizeof(char), 1, fp);
        strcat(buffer_amount_mazes, buffer);
    }

    amount_mazes = atoi(buffer_amount_mazes); // convert buffer to actual amount of mazes

    fgetc(fp); // move as 1
    free(buffer);

    return amount_mazes;
}

int main() {
    // create file pointers
    FILE *fp = fopen("data_structure_and_algorithm/input.txt", "r");
    FILE *fp_out = fopen("data_structure_and_algorithm/output_ex.txt", "w");

    // initialization variables
    int amount_mazes = 0, directions = 0;
    char *buffer = (char *)malloc(sizeof(char));
    char *buffer_size = (char *)malloc(sizeof(char) * 20);
    char *tok, *temp;
    SIZE size = {0, 0};
    
    // get amount of all mazes
    if (ftell(fp) == 0)
        amount_mazes = findAmountMaze(fp);    

    // if amount_mazes is 0, then quit program
    if (amount_mazes == 0) {
        fclose(fp_out);
        fclose(fp);
        return 0;
    }

    // get size of maze
    while (amount_mazes > 0) {
        if (buffer == NULL)
            buffer = (char *)malloc(sizeof(char) * 2);

        amount_mazes--;
        size.row = 0; size.col = 0;

        // find rows and columns of a maze
        // and get integer values and put these into each members of struct size
        while (strcmp(buffer, "\r") != 0) {
            if (size.row == 0 || size.col == 0) {
                memset(buffer_size, 0, sizeof(char) * 20);
                memset(buffer, 0, sizeof(char) * 2);
            }

            fread(buffer, sizeof(char), 1, fp);
            strcpy(buffer_size, buffer);

            if (size.row == 0) {
                while (strcmp(buffer, " ")) {
                    fread(buffer, sizeof(char), 1, fp);
                    strcat(buffer_size, buffer);
                }
                size.row = atoi(buffer_size);
            }
            else if (size.col == 0) {
                while (strcmp(buffer, "\r")) {
                    fread(buffer, sizeof(char), 1, fp);
                    strcat(buffer_size, buffer);
                }
                size.col = atoi(buffer_size);
            }
        }

        fgetc(fp);

        free(buffer);

        // debug
        printf("%d %d\n", size.row, size.col);

        // allocate dynamic memory of maze
        buffer = (char *)malloc(sizeof(char) * 2);
        int **arr = (int **)malloc(sizeof(int *) * size.row);

        for (int i = 0; i < size.row; i++) {
            arr[i] = (int *)malloc(sizeof(int) * size.col);
        }

        // get a maze with conditions
        for (int i = 0; i < size.row; i++) {
            for (int j = 0; j < size.col; j++) {
                fread(buffer, sizeof(char), 2, fp);

                if (strcmp(buffer, " ") == 0) {
                    j--;
                    continue;
                }

                // save value into array
                arr[i][j] = atoi(buffer);
            }

            // make fp to go down a line
            fgetc(fp);
            fgetc(fp);
        }

        // debug code
        for (int i = 0; i < size.row; i++) {
            for (int j = 0; j < size.col; j++) {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }

        // free the maze array
        for (int i = 0; i < size.row; i++) {
            free(arr[i]);
        }
        
        free(arr);
        free(buffer);

        buffer = NULL;
    }

    free(buffer_size);
    free(buffer);
    fclose(fp_out);
    fclose(fp);

    return 0;
}