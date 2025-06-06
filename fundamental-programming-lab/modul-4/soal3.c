#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int arr[], int size) {
    int *leftPtr = arr;
    int *rightPtr = arr + (size - 1);
    while((leftPtr < rightPtr) && (leftPtr != rightPtr)) {
        printf("%d\n", *leftPtr);
        printf("%d\n", *rightPtr);
        swap(leftPtr, rightPtr);
        leftPtr += 1;
        rightPtr -= 1;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    reverse(arr, n);
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[n]);
    }
}