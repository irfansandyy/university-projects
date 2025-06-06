#include <stdio.h>

int faktorial(int n, int sum) {
    if(n == 0) return 1;
    if(n == 1) return sum;
    return faktorial(n - 1, sum)*n;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", faktorial(n, 1));
}