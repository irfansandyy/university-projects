#include <stdio.h>

int pola(int n);

int main() {
    int n = 5;
    printf("Pola ke %d adalah %d", n, pola(n));
}

int pola(int n) {
    if(n <= 1) return 1;
    return n*n + pola(n-1);
}