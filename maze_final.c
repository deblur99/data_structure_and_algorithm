#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_LENGTH 2
#define BUFFER_SIZE_LENGTH 20
#define BUFFER_AMOUNT_MAZES_LEGNTH 5
#define DIRECTION_BUFFER_LENGTH 10

static int result = 0;

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

// pre-execute before executing main problem: for reducing execute time
// from the solution of task 1
int isExistPath(int row_position, int col_position, int row_size, int col_size, int *(arr)[col_size]) {

    // Idea:
        // 위->아래->위 (0, 0), 0 -> (1, 0), 0 -> (0, 0), 1
        // 아래->위->아래 (1, 1), 2 -> (0, 1), 1 -> (1, 1), 0
        // 이전 단계의 row만 볼 수 있음 -> 핵심은 현 단계 row와 이전의 이전 단계 row의 비교

        // 이미 지나간 경로로 가지 않기 위한 규칙
        // 이전에 위에서 내려온 경우: 위로 다시 갈 수 없으므로 오른쪽 또는 아래쪽으로 진행 가능
        // 이전에 아래에서 올라온 경우: 아래로 다시 갈 수 없으므로 위쪽 또는 오른쪽으로 진행 가능
        // 이전에 왼쪽에서 오른쪽으로 온 경우: 왼쪽으로 가는 동작은 없으므로 위쪽 또는 오른쪽 또는 아래쪽으로 진행 가능

    if (row_position < 0)
        return 0;

    if (row_position == row_size || col_position == col_size)
        return 0;

    if (arr[row_position][col_position] == 0)
        return 0;

    if ((arr[row_position][col_position] == 1) && (row_position == row_size - 1) && (col_position == col_size - 1)) {
        return 1;
    }
    
    if (arr[row_position][col_position] != 2) {
        arr[row_position][col_position] = 2; // already went
        
        // each function call means going up, going right, going down
        return (isExistPath(row_position - 1, col_position, row_size, col_size, arr) +
                isExistPath(row_position, col_position + 1, row_size, col_size, arr) +
                isExistPath(row_position + 1, col_position, row_size, col_size, arr));
    } else {
        return 0;
    }
}

// main problem: find directions of maze
int findDirection(int row_position, int col_position, int row_size, int col_size, int *(arr)[col_size], bool cameFromUp, bool cameFromDown) {

   // Idea:
        // 위->아래->위 (0, 0), 0 -> (1, 0), 0 -> (0, 0), 1
        // 아래->위->아래 (1, 1), 2 -> (0, 1), 1 -> (1, 1), 0
        // 이전 단계의 row만 볼 수 있음 -> 핵심은 현 단계 row와 이전의 이전 단계 row의 비교

        // 정방향으로 간다고 했을 때는 위쪽과 아래쪽으로 확인하는데, 이럴 경우 위로 갔다가 아래로 가거나 그 반대 방향일 때
        // 무한정 호출하는 경우가 발생하여 프로그램이 멈춘다.

        // 따라서 다음과 같은 아이디어로 알고리즘을 구현하였다.
        // 출발지에서 도착지로 가는 방향과 정반대로, 도착지에서 출발하여 출발지에 도착하는 것을 경로 1개로 침
        // 이처럼 반대로 간다면, 출발지에서 도착지까지 위쪽-오른쪽-아래쪽 3개 방향이 위쪽-왼쪽 2개 방향으로 줄어듦
        // 또한, 도착지 근처에 있는 0을 빠르게 발견하면, 0을 반환함으로써 처리 시간을 대폭 줄일 수 있음

    // if result exceeds to 1000000, change it 1000000
    if (result >= 1000000) {
        result = 1000000;
        return 0;
    }

    if ((row_position < 0) || (col_position < 0))
        return 0;

    if ((row_position >= row_size) || (col_position >= col_size))
        return 0;

    if (arr[row_position][col_position] == 0)
        return 0;

    if ((arr[row_position][col_position] == 1) && (row_position == (row_size - 1)) && (col_position == (col_size - 1))) {
        result++;
        return 1;
    }        

    if (cameFromUp)
        return (findDirection(row_position + 1, col_position, row_size, col_size, arr, true, false) +
                findDirection(row_position, col_position + 1, row_size, col_size, arr, false, false));

    else if (cameFromDown) 
        return (findDirection(row_position - 1, col_position, row_size, col_size, arr, false, true) +
                findDirection(row_position, col_position + 1, row_size, col_size, arr, false, false));

    else 
        return (findDirection(row_position - 1, col_position, row_size, col_size, arr, false, true) +
                findDirection(row_position, col_position + 1, row_size, col_size, arr, false, false) +
                findDirection(row_position + 1, col_position, row_size, col_size, arr, true, false));
}

int main() {
    // create file pointers
    FILE *fp = fopen("data_structure_and_algorithm/input.txt", "r");
    FILE *fp_out = fopen("data_structure_and_algorithm/output.txt", "w");

    // initialization variables
    int isExist = 0;
    int amount_mazes = 0, directions = 0;
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

        // copy to arr_copy to preserve original data of the maze
        int **arr_copy = (int **)malloc(sizeof(int *) * size.row);

        for (int i = 0; i < size.row; i++) {
            arr_copy[i] = (int *)malloc(sizeof(int) * size.col);
        }

        for (int i = 0; i < size.row; i++) {
            for (int j = 0; j < size.col; j++) {
                arr_copy[i][j] = arr[i][j];
            }
        }

        // find a number of directions of the maze
        position.row = 0;
        position.col = 0;
        result = 0;

        // justify that paths of the maze is exist (by using task 1 method)
        isExist = isExistPath(position.row, position.col, size.row, size.col, arr);        

        // if isExist is true, then search all paths of the maze
        if (isExist >= 1)
            findDirection(position.row, position.col, size.row, size.col, arr_copy, false, false);

        // free copy of the maze
        for (int i = 0; i < size.row; i++) {
            free(arr_copy[i]);
        }

        free(arr_copy);
        
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