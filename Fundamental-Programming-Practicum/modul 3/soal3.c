#include <stdio.h>
#include <limits.h>

int max(int arr[], int arrSize);
int min(int arr[], int arrSize);

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int arrSize = sizeof(arr);
    printf("Max: %d", max(arr, arrSize));
    printf("Min: %d", min(arr, arrSize));
}

int max(int arr[], int arrSize) {
    int n = INT_MIN;
    for(int i = 0; i < (int)sizeof(arrSize)/__SIZEOF_INT__; i++){
        if(arr[i] > n) n = arr[i];
    }
    return n;
}

int min(int arr[], int arrSize) {
    int n = INT_MAX;
    for(int i = 0; i < (int)sizeof(arrSize)/__SIZEOF_INT__; i++){
        if(arr[i] < n) n = arr[i];
    }
    return n;
}