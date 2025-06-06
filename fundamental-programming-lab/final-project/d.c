#include <stdio.h>
#include <string.h>
#define ll long long

int main() {
    char nama[10];
    ll hasil = 0;
    ll n;
    scanf("%s", nama);
    scanf("%lld", &n);
    if(!strcmp(nama, "Ellie")) {
        for(int i = 2; i <= n; i += 2) hasil += i;
        printf("%lld", hasil);
    } else if(!strcmp(nama, "Oddie")) {
        for(int i = 1; i <= n; i += 2) hasil += i;
        printf("%lld", hasil);
    } else {
        printf("Who is that?");
    }
}