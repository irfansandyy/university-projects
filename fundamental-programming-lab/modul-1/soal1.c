#include <stdio.h>

int main() {
    int num, d1, d2, d3, ndigits, total = 0;
    scanf("%d", &num);
    d1 = num % 10;
    d2 = (num / 10) % 10;
    d3 = num / 100;
    
    if(num < 10) {
        ndigits = 1;
    } else if(num < 100) {
        ndigits = 2;
    } else {
        ndigits = 3;
    }

    if(ndigits == 1) {
        total += d1;
    } else if(ndigits == 2) {
        total += d1*d1;
        total += d2*d2;
    } else {
        total += d1*d1*d1;
        total += d2*d2*d2;
        total += d3*d3*d3;
    }

    if(num == total) {
        printf("Merupakan Bilangan Armstrong\n");
    } else {
        printf("Bukan Merupakan Bilangan Armstrong\n");
    }
}