#include <stdio.h>

int getSum(int n) {
    if (n == 1) {
        return 1;
    } else {
        return n + getSum(n - 1);
    }
}

int main() {
    int result = getSum(10);

    printf("%d\n", result);
}