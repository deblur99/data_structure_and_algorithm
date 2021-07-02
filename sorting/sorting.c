//
// Created by 한현민 on 2021-06-30.
//

#include <stdio.h>

void selection_sort(int *arr, int length) {
    int min;
    int temp;

    for (int i = 0; i < length - 1; i++) {
        min = i;

        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[min])
                min = j;
        }

        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}