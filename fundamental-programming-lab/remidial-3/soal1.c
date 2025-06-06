#include <stdio.h>
#define llu long long unsigned

void pola(int n, llu p0, llu p1, llu p2, int start, llu list[]) {
    list[start] = p2;
    if(n < 2) return;
    if(start > n) return;
    return pola(n, list[start - 1], list[start], p0+p1+p2, start+1, list);
}

void printlist(llu list[], int ctr, int num) {
    if(num%2 == ctr%2) printf("%llu ", list[ctr]);
    if(ctr <= 0) return;
    return printlist(list, ctr-1, num);
}

int main() {
    int n;
    scanf("%d", &n);
    llu p[100];
    p[0] = 0;
    p[1] = 1;
    p[2] = 2;
    pola(n, 0, 1, 2, 2, p);
    printlist(p, n, n);
    return 0;
}