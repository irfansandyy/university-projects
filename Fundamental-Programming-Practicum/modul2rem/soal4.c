#include <stdio.h>
#define MAX_N 1000

int main() {
    int n;
    scanf("%d", &n);
    int l[n][n];
    int counter = 1;
    int i = 0;
    int j = 0;
    int xloffset = 0;
    int yuoffset = 0;
    int xroffset = 0;
    int ydoffset = 0;
    while(counter <= n*n) {
        for(; j  < n - xloffset; j++) {
            if(counter <= n*n) {
                l[i][j] = counter;
                counter++;
            }
        }
        xloffset++;
        j--;
        i++;
        for(; i < n - yuoffset; i++) {
            if(counter <= n*n) {
                l[i][j] = counter;
                counter++;
            }
        }
        yuoffset++;
        i--;
        j--;
        for(; j >= 0 + xroffset; j--) {
            if(counter <= n*n) {
                l[i][j] = counter;
                counter++;
            }
        }
        xroffset++;
        j++;
        i--;
        ydoffset++;
        for(; i >= 0 + ydoffset; i--) {
            if(counter <= n*n) {
                l[i][j] = counter;
                counter++;
            }
        }
        i++;
        j++;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", l[i][j]);
        }
        printf("\n");
    }
}