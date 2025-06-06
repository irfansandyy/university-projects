#include <stdio.h>
#include <math.h>
#define MAX_TEST_SIZE 4096

int main() {
    long long n, m, f, k = 0;
    int bin_n[64] = {0};
    int bin_k[64] = {0};

    scanf(" %lld %lld %lld", &n, &m, &f);

    if(n > m) { //karena n XOR 0 = n
        printf("HAHAHA, I CAN SAVE THE WORLD");
        return 0;
    }
    for(long long i = f; i >= ((f - MAX_TEST_SIZE) >= 0) ? f - MAX_TEST_SIZE : 0; i--) {
        if((n ^ i) - 1 >= m) {
            printf("HAHAHA, I CAN SAVE THE WORLD");
            return 0;
        }
    }

    long long numn = n;
    int it = 63;
    for( ;numn > 0; it--) {
        bin_n[it] = numn % 2;
        numn /= 2;
    }
    
    int iter = 63 - (int) ceil(log(n)/log(2));
    for(int i = iter; i < 64; i++) { 
        if(bin_n[i] == 0) {
            bin_k[i] = 1;
        }
    }
    
    do {
        k = 0;
        for(int i = 0; i < 64; i++) {
            int exp = 63 - i;
            int base = 2;
            long long power_result = 1;
            for (;;) {
                if(exp & 1) power_result *= base;
                exp >>= 1;
                if(!exp) break;
                base *= base;
            }
            k += power_result*bin_k[i];
        }
        
        for(int i = 0; i < 64; i++) printf("%d", bin_k[i]);
        printf("\n%lld\n", k);

        if(bin_n[iter] == 0) {
            bin_k[iter] = 0;
        } else {
            bin_k[iter] = 1;
        }
        if(((n^k)-1 >= m) && (k <= f)) {
            printf("HAHAHA, I CAN SAVE THE WORLD");
            return 0;
        }
        iter++;
    }
    while(iter < 65);
    printf("OH NOOO, I FAILED");
}