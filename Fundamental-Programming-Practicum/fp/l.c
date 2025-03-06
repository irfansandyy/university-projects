#define __USE_MINGW_ANSI_STDIO
#include <stdio.h>
#include <math.h>

// t = 2r
// V = 2 pi * r * r * r
// r = V / 2 pi
// lp = 2 pi * r * r + 4 pi * r * r 
int main() {
    long double PI = 3.14159265358979323846;
    long double v, r, lp;
    scanf("%Lf", &v);
    r = cbrtl(v / (2*PI));
    lp = 2*PI*r*r + 4*PI*r*r;
    printf("Luas permukaan: %.2Lf", lp);
}