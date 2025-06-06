#include <stdio.h>
#include <math.h>

int main() {
    long long n, m, f, k = 0;
    int bin_n[64] = {0};
    int bin_f[64] = {0};

    scanf("%lld %lld %lld", &n, &m, &f);

    if((n ^ f) - 1 >= m) {
        printf("HAHAHA, I CAN SAVE THE WORLD");
        return 0;
    }

    long long numn = n;
    long long numf = f;

    for(int i = 0 ;numn > 0; i++) {
        bin_n[i] = numn % 2;
        numn /= 2;
    }

    for(int i = 0 ;numf > 0; i++) {
        bin_f[i] = numf % 2;
        numf /= 2;
    }
    
    int iter = (int) ceil(log(f)/log(2));
    if(f > n) {
        for(int i = iter; i >= 0; i--) {
            if((bin_f[i] == 1) && (bin_n[i] == 0)) {
                k += pow(2, i);
            }
        }
    } else if(f <= n) {
        if(bin_f[iter] == bin_n[iter]) {
            for(int i = iter - 1; i >= 0; i--) {
                if(bin_n[i] == 0) {
                    k += pow(2, i);
                }
            }
        } else {
            int skip_condition = 0;
            for(int i = iter; i >= 0; i--) {
                if((skip_condition == 1) && (bin_n[i]==0)){
                        k += pow(2, i);
                        continue;
                    } 
                if((bin_n[i] == 0) && (bin_f[i] == 1)) {
                    k += pow(2, i);
                } else if((bin_n[i] == 1) && (bin_f[i] == 1)) {
                    skip_condition = 1;
                }
            }
        }
    }
    if(((n ^ k) - 1) >= m) {
        printf("HAHAHA, I CAN SAVE THE WORLD");
    } else {
        printf("OH NOOO, I FAILED");
    }
}