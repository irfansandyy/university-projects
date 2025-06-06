#include <stdio.h>

int main() {
    int n;
    printf("Input the power: ");
    scanf("%d", &n);
    if(n >= 0) {
        printf("1");
        for(int i = 0; i < n; i++) {
            printf("00");
        }
    } else if(n < 0) {
        printf("0.0");
        for(int i = 0; i < (n*-1) - 1; i++) {
            printf("00");
        }
        printf("1");
    }
}