#include <stdio.h>
#define ll long long

ll kpk(int x, int y) {
    ll tempX = x;
    ll tempY = y;
    while(tempX != tempY) {
        if(tempX > tempY) tempY += y;
        else if(tempX < tempY) tempX += x;
    }
    return tempX;
}

int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%lld", kpk(x, y));
}