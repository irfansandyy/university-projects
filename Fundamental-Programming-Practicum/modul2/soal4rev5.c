#include <stdio.h>
#include <math.h>

int main() {
    long long n, m, f, k = 0;
    int bin_n[64] = {0};
    int bin_f[64] = {0};

    scanf(" %lld %lld %lld", &n, &m, &f);

    if((n ^ f) - 1 >= m) {
        printf("HAHAHA, I CAN SAVE THE WORLD");
        return 0;
    }

    long long numn = n;
    long long numf = f;
    int iter = 64 - ((int) ceil(log(f)/log(2)));

    for(int i = 63 ;numn > 0; i--) {
        bin_n[i] = numn % 2;
        bin_f[i] = numf % 2;
        numn /= 2;
        numf /= 2;
    }
    
    if(f > n) {
        for(int i = iter; i < 64; i++) {
            if((bin_f[i] == 1) && (bin_n[i] == 0)) {
                k += pow(2, 63 - i);
            }
        }
    } else {
        if(bin_f[iter] == bin_n[iter]) {
            for(int i = iter + 1; i < 64; i++) {
                if(bin_n[i] == 0) {
                    k += pow(2, 63 - i);
                }
            }
        } else {
            int i = iter;
            while(i < 64) {
                if((bin_f[i] == 1) && (bin_n[i] == 0)) {
                    k += pow(2, 63 - i);
                } else if((bin_f[i] == 1) && (bin_n[i] == 1)) {
                    i++;
                    break;
                }
                i++;
            }
            while(i < 64) {
                if(bin_n[i] == 0) {
                    k += pow(2, 63 - i);
                }
                i++;
            }
        }
    }
    if(((n ^ k) - 1) >= m) {
        printf("HAHAHA, I CAN SAVE THE WORLD");
    } else {
        printf("OH NOOO, I FAILED");
    }
}