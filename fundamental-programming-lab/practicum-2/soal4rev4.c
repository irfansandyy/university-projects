#include <stdio.h>
#include <math.h>

int main() {
    long long n, m, f, k = 0;
    int bin_n[64] = {0};
    int bin_k[64] = {0};

    scanf(" %lld %lld %lld", &n, &m, &f);
    long long numn = n;

    for(int i = 63 ;numn > 0; i--) {
        bin_n[i] = numn % 2;
        numn /= 2;
    }
    int iter = 63 - (int) ceil(log(f)/log(2));
    for(int i = iter ; i < 64; i++) {
        if(bin_n[i] == 0) {
            bin_k[i] = 1;
        } else if(bin_n[i] == 1) {
            bin_k[i] = 0;
        }
    }
    
    while(iter < 64) {
        for(int i = 1; i >= 0; i--) {
            bin_k[iter] = i;

            k = 0;
            int multiplier = 1;
            for(int j = 0; j < 64; j++) {
                k += multiplier*bin_k[63 - j];
                multiplier *= 2;
            }

            if(((n^k)-1 >= m) && (k <= f)) {
                printf("HAHAHA, I CAN SAVE THE WORLD");
                return 0;
            }
        }
        iter++;
    }
    printf("OH NOOO, I FAILED");
    return 0;
}