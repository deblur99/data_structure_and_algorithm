#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 2
#define BUFFER_SIZE_LENGTH 20
#define BUFFER_AMOUNT_MAZES_LEGNTH 5
#define DIRECTION_BUFFER_LENGTH 10

typedef struct size {
    int row;
    int col;
}SIZE;

// find actual amount of mazes in the file
int findAmountMaze(FILE *fp) {

    int amount_mazes;
    char *buffer = (char *)malloc(sizeof(char));
    char buffer_amount_mazes[BUFFER_AMOUNT_MAZES_LEGNTH];

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

// main problem: find directions of maze
int findDirection(int row_position, int col_position, SIZE size, int *(arr)[size.col]) {
    if (row_position < 0 || row_position >= size.row || col_position >= size.col)
        return 0;

    if (arr[row_position][col_position] == 0)
        return 0;

    if ((row_position == size.row - 1) && (col_position == size.col - 1)) {
        printf("Found the destination\n");
        return 1;
    }
        
    else {      // each up way, right way, left way 
        return (findDirection(row_position - 1, col_position, size, arr) +
               findDirection(row_position, col_position + 1, size, arr) +
               findDirection(row_position + 1, col_position, size, arr));
    }
}

int main() {
    // create file pointers
    FILE *fp = fopen("data_structure_and_algorithm/input_ex.txt", "r");
    FILE *fp_out = fopen("data_structure_and_algorithm/output_ex.txt", "w");

    // initialization variables
    int amount_mazes = 0, directions = 0, result = 0;
    char *buffer = NULL;
    char *buffer_size = NULL;
    char *tok;
    char temp[DIRECTION_BUFFER_LENGTH] = {'\0', };

    SIZE size = {0, 0};
    SIZE position = {0, 0};
    
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
            buffer = (char *)malloc(sizeof(char) * BUFFER_LENGTH);

        amount_mazes--;
        size.row = 0; size.col = 0;

        // find rows and columns of a maze
        // and get integer values and put these into each members of struct size
        while (strcmp(buffer, "\r") != 0) {
            if (size.row == 0 || size.col == 0) {
                buffer_size = (char *)malloc(sizeof(char) * BUFFER_SIZE_LENGTH);
                memset(buffer_size, 0, sizeof(char) * BUFFER_SIZE_LENGTH);
                memset(buffer, 0, sizeof(char) * BUFFER_LENGTH);
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

        free(buffer_size);
        free(buffer);

        buffer_size = NULL;
        buffer = NULL;

        // debug
        //printf("%d %d\n", size.row, size.col);

        // allocate dynamic memory of maze
        buffer = (char *)malloc(sizeof(char) * BUFFER_LENGTH);
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
        /*
        for (int i = 0; i < size.row; i++) {
            for (int j = 0; j < size.col; j++) {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }
        */

        // find a number of directions of the maze
        position.row = 0; position.col = 0;
        result = findDirection(position.row, position.col, size, arr);
        
        // write a number of directions of the maze into output.txt
        sprintf(temp, "%d\n", result);
        fwrite(temp, sizeof(char), strlen(temp), fp_out);

        memset(temp, 0, DIRECTION_BUFFER_LENGTH);

        // free the maze array
        for (int i = 0; i < size.row; i++) {
            free(arr[i]);
        }
        
        free(arr);
        free(buffer);

        arr = NULL;
        buffer = NULL;
    }

    free(buffer);
    buffer = NULL;

    fclose(fp_out);
    fclose(fp);

    return 0;
}