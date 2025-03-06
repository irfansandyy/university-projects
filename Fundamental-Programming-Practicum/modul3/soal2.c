#include <stdio.h>
#define llu long long unsigned

llu sumofprevious(int n, llu sum) {
    if(n==0) return sum;
    return sumofprevious(n-1, sum + n);
}

llu pola(int target, llu sum, int counter) {
    if(target + 1 == counter) return sum;
    return pola(target, 2*sum + sumofprevious(counter, 0), counter + 1);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%llu", pola(n, 0, 1));
}