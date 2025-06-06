#include <stdio.h>
#include <math.h>

int fpb(int x, int y) {
    if(y == 0) return x;
    else fpb(y, x%y);
}

int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d", fpb(x, y));
}