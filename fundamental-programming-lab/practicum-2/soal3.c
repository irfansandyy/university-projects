#include <stdio.h>
#include <math.h>
#define MAX_N_SIZE 100001

int main() {
    int t;
    scanf("%d", &t);
    int freq[MAX_N_SIZE] = {0};
    int max_n = 0;
    int prime = 1;
    for(int i = 0; i < t; i++) {
        int temp;
        scanf("%d", &temp);
        if(max_n < temp) max_n = temp;
        ++freq[temp];
    }
    int modus = freq[0];
    int modus_n = 0;
    for(int i = 1; i <= max_n; i++) {
        if(freq[i] >= modus) {
            modus = freq[i];
            modus_n = i;
        }
    }
    for(int i = 2; i <= (int) sqrt(modus_n); i++) {
        if(modus_n % i == 0) {
            prime = 0;
        }
    }
    printf("Modus: %d\n", modus_n);
    if((prime == 1 && !(modus_n == 1))) {
        printf("Wah, modusnya prima nihh.");
    } else {
        printf("Yah, modusnya gak prima.");
    }
}