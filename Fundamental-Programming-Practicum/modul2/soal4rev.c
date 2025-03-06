#include <stdio.h>
#include <time.h>
#define MAX_TEST_SIZE 281474976710656

int main() {
    long long n, m, f;
    int bensin_cukup = 0;
    scanf(" %lld %lld %lld", &n, &m, &f);
    if(n > m) { //karena n XOR 0 = n
        bensin_cukup = 1;
    }
    if(bensin_cukup == 0) {
        for(long long i = f; i >= ((f - MAX_TEST_SIZE) >= 0) ? f - MAX_TEST_SIZE : 0; i--) {
            if((n ^ i) - 1 >= m) {
                bensin_cukup = 1;
                break;
            }
        }
    }
    if(bensin_cukup == 1) {
        printf("HAHAHA, I CAN SAVE THE WORLD");
    } else {
        printf("OH NOOO, I FAILED");
    }
}