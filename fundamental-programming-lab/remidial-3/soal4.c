#include <stdio.h>
#define ll long long

ll fx(ll x) {
    if(x%2 == 0) return x/2;
    else return 2*x;
}

ll gx(ll x) {
    if(x%2 == 0) return x + 2;
    else return x - 2;
}

ll function(ll x, ll init, int n, int start) {
    if(start > n) return x - init;
    else if(start%2 == 1) return function(fx(x) + init , init, n, start + 1);
    else return function(gx(x) + init, init, n, start + 1);
}

int main() {
    ll x;
    int n;
    scanf("%lld %d", &x, &n);
    printf("%lld", function(x, x, n, 1));
}