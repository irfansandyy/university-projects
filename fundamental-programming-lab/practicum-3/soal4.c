#include <stdio.h>
#define llu long long unsigned

llu pola(int n, llu sum) {
    if(n == 1) return 2;
    return 3*pola(n-1, sum + n);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("Ada %llu model, bebaskan aku!", pola(n, 0));
}