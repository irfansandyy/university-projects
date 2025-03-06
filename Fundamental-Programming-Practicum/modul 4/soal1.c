#include <stdio.h>

void tambah(int x, int y, int* z) {
    *z = x + y;
}

int main() {
    int a = 1;
    int b = 2;
    int c;
    tambah(a, b, &c);
    printf("%d", c);
}