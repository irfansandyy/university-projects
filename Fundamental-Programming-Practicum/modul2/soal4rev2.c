#include <stdio.h>
#include <math.h>

int main() {
    long long n, m, f, k = 0;
    int bin_f[64] = {0};
    int bin_k[64] = {0};

    scanf(" %lld %lld %lld", &n, &m, &f);

    long long numf = f;
    int it = 63;
    for( ;numf > 0; it--) {
        bin_f[it] = numf % 2;
        numf /= 2;
    }
    printf("%d\n", bin_f[0]);
    
    int iter = 63 - (int) ceil(log(f)/log(2));
    int times = 0;
    do {
        times += 1;
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
        
        if(times % 2 == 1) { 
            bin_k[iter] = 1;
            iter--;
        } else {
            bin_k[iter] = 0;
        }
        if(((n^k)-1 >= m) && (k <= f)) {
            printf("HAHAHA, I CAN SAVE THE WORLD");
            return 0;
        }
        iter++;
    }
    while(iter < 64);
    printf("OH NOOO, I FAILED");
}