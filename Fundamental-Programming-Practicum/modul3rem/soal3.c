#include <stdio.h>
#define llu long long unsigned

llu fpb(llu d, llu h) {
    if(h == 0) return d;
    return fpb(h, d%h);
}

int main() {
    llu d, h;
    scanf("%llu %llu", &d, &h);
    if(h > d) {
        llu temp = d;
        d = h;
        h = temp;
    }
    printf("%llu", fpb(d, h));
}