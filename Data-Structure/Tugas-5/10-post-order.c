#include <stdio.h>
#define SIZE 14

void postOrder(int num[], int i, int n) {
    if (i > n) return;
    postOrder(num, 2 * i, n);
    postOrder(num, 2 * i + 1, n);
    printf("%d ", num[i]);
}

int main() {
    int num[SIZE] = {0, 47, 26, 64, 18, 35, 56, 73, 13, 21, 30, 39, 61, 75};
    postOrder(num, 1, 13);
    return 0;
}
