#include <stdio.h>

int main() {
    long long n, m, f;
    int bensin_cukup = 0;
    scanf(" %lld %lld %lld", &n, &m, &f);
    for(long long i = ((f - 256) >= 0) ? f - 256 : 0; i <= f; i++) {
        if((n ^ i) - 1 >= m) {
            bensin_cukup = 1;
        }
    }
    if(bensin_cukup == 1) {
        printf("HAHAHA, I CAN SAVE THE WORLD");
    } else {
        printf("OH NOOO, I FAILED");
    }
}