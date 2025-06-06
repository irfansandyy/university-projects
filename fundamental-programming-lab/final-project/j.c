#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    int row;
    int col;
} Data;

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    int target;

    scanf("%d %d", &n, &m);
    Data arr[n*m];
    
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++, index++) {
            scanf("%d", &arr[index].num);
            arr[index].row = i;
            arr[index].col = j;
        }
    }
    
    scanf("%d", &target);

    qsort(arr, n*m, sizeof(Data), compare);
    
    int left = 0;
    int right = n * m - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid].num == target) {
            printf("Element %d found at position: (%d, %d).", target, arr[mid].row+1, arr[mid].col+1);
            return 0;
        }
        
        if (arr[mid].num < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("Element %d not found.", target);
}