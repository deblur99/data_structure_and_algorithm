//
// Created by 한현민 on 2021-06-30.
//

#include <stdio.h>
#include "sorting.h"

#define LENGTH 10

int main() {
    int arr[LENGTH] = {12, 2, 55, 42, 25, 1, 9, 0, 34, 18};

    selection_sort(arr, LENGTH);

    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}