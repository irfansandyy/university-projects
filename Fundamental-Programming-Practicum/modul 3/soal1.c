#include <stdio.h>

int faktorial(int n);

int main() {
    int n = 6;
    printf("hasil dari %d adalah %d", n, faktorial(n));
}

int faktorial(int n) {
    if(n <= 1) return 1;
    return n * faktorial(n - 1);
}