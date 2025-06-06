#include <stdio.h>

int main() {
    long long x1, y1, x2, y2;
    scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
    double grad, tipotY;
    if(x2-x1 != 0) {
        grad = (double)(y2-y1)/(x2-x1);
        tipotY = y1 - grad*x1;
        printf("%.2lf %.2lf", grad, tipotY);
    } else {
        printf("-_-");
    }
}