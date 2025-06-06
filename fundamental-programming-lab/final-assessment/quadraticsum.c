#include <stdio.h>

int main() {
    int a;
    long long unsigned sum = 0;
    scanf("%d", &a);
    for(int i = 1; i <= a; i++) {
        sum += i*i;
    }
    printf("%llu", sum);
}