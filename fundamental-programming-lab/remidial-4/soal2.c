#include <stdio.h>

void numbersAddition(int *arr1, int *arr2, int n) {
    int* arr1ptr = arr1;
    int* arr2ptr = arr2 + n - 1;
    while(arr1ptr < arr1 + n) {
        *arr1ptr = *arr1ptr + *arr2ptr;
        arr1ptr++;
        arr2ptr--;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr1[n], arr2[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr2[i]);
    }
    numbersAddition(arr1, arr2, n);
    for(int i = 0; i < n; i++) {
        printf("%d ", arr1[i]);
    }

    return 0;
}