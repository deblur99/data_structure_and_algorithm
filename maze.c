#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct size {
    int row;
    int col;


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
    buffer = NULL;

    return amount_mazes;
}

// find rows and columns of a maze
SIZE getSizeOfMaze(FILE *fp) {

    SIZE size;
    char *buffer = (char *)malloc(sizeof(char));
    char *buffer_size = (char *)malloc(sizeof(char) * 20);
    char *tok, *temp;

    while (strcmp(buffer, "\r") != 0) {
        fread(buffer, sizeof(char), 1, fp);
        strcat(buffer_size, buffer);
    }
    
    // find integer values and put these into each members of struct size
    tok = strtok(buffer_size, " ");
    temp = tok;
    size.row = atoi(temp);

    tok = strtok(NULL, " ");
    temp = tok;
    size.col = atoi(tok);

    // exception: if there are more than two values that implying row and column line,
    //            all members in structure will have 0 and be returned.
    tok = strtok(NULL, " ");
    if (tok != NULL) {
        printf("Error: Invalid Input size\n");
        size.row = 0; size.col = 0;
        return size;
    }

    fgetc(fp); // move from "\n" to first value
    free(buffer_size);
    free(buffer);

    buffer_size = NULL;
    buffer = NULL;

    return size;
}

// get a maze from the file
int** getMaze(FILE *fp, SIZE size) {

    // allocate dynamic memory
    char *buffer = (char *)malloc(sizeof(char) * 2);
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

    free(buffer);
    buffer = NULL;

    // return the gotten maze
    return arr;
}

// actual main function
int findDirections(int *maze[], int row, int col);

int main() {
    FILE *fp = fopen("data_structure_and_algorithm/input_ex.txt", "r");
    FILE *fp_out = fopen("data_structure_and_algorithm/output_ex.txt", "w");

    // initialization
    int amount_mazes = 0, directions = 0;
    
    // get amount of all mazes
    if (ftell(fp) == 0)
        amount_mazes = findAmountMaze(fp);    

    if (amount_mazes == 0) {
        fclose(fp_out);
        fclose(fp);
        return 0;
    }      
    
    // get size of maze
    while (amount_mazes > 0) {
        amount_mazes--;

        SIZE size_of_maze = getSizeOfMaze(fp);

        // get a maze
        int **maze = getMaze(fp, size_of_maze);

        // find directions of the maze
        directions = findDirections(maze, size_of_maze.row, size_of_maze.col);

        // debug code
        printf("%d %d\n", size_of_maze.row, size_of_maze.col);
        for (int i = 0; i < size_of_maze.row; i++) {
            for (int j = 0; j < size_of_maze.col; j++)
                printf("%d ", maze[i][j]);
            printf("\n");
        }    

        // free dynamic memories and close file pointers
        for (int i = 0; i < size_of_maze.row; i++) {
            free(maze[i]);
        }

        free(maze);
        maze = NULL;

        printf("%ld\n", ftell(fp));
        char buffer[1];
        fread(buffer, sizeof(char), 1, fp);
        printf("%d\n", atoi);
        printf("%ld\n", ftell(fp));
    }

    fclose(fp_out);
    fclose(fp);

    return 0;
}

int findDirections(int *maze[], int row, int col) {
    return 0;
}