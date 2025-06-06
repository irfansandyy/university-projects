#include <stdio.h>

int main() {
    long long x, y, z, terbanyak, terdikit, samaNilai = 0;
    int adayangsama = 0;
    scanf(" %lld %lld %lld", &x, &y, &z);
    
    if(x == y) {
        samaNilai = x;
        adayangsama = 1;
    } else if(x == z) {
        samaNilai = x;
        adayangsama = 1;
    } else if(y == z) {
        samaNilai = y;
        adayangsama = 1;
    }

    terbanyak = x;
    terdikit = x;
    if(y > terbanyak) {
        terbanyak = y;
    }
    if(z > terbanyak) {
        terbanyak = z;
    }
    if(y < terdikit) {
        terdikit = y;
    }
    if(z < terdikit) {
        terdikit = z;
    }

    printf("Stok terbanyak : %lld", terbanyak);
    printf("\nStok terendah : %lld", terdikit);
    if(adayangsama) {
        printf("\nTerdapat toko dengan stok yang sama : %lld", samaNilai);
    } else {
        printf("\nTidak ada stok yang sama");
    }
    return 0;
}