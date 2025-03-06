#include <stdio.h>

int main() {
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);
    for(int i = 0; i < n; i++) {
        printf("%d\n", (1 + i * k)%n);
    }
}