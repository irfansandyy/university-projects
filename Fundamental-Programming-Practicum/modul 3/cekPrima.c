#include <stdio.h>
#include <math.h>

int cekPrima(int num);

int main() {
    int arr[] = {2, 9, 16, 25, 49, 50, 12, 13};
    for(int i = 0; i < (int)sizeof(arr)/__SIZEOF_INT__; i++) {
        if(cekPrima(arr[i])) {
            printf("Bilangan %d Merupakan Bilangan Prima\n", arr[i]);
        } else {
            printf("Bilangan %d Bukan Bilangan Prima\n", arr[i]);
        }
    }
}

int cekPrima(int num) {
    if(num <= 1) return 0;
    for(int i = 2; i <= (int) sqrt(num); i++) {
        if(num % i == 0) {
            return 0;
        }
    }
    return 1;
}