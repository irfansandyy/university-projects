#include <stdio.h>
#include <string.h>
#define MAX_SLIME 10

int main() {
    int t;
    scanf("%d", &t);
    for(int i = 0; i < t; i++) {
        int n, e;
        int s[MAX_SLIME] = {0};
        int total = 0;
        scanf("%d", &n);
        for(int j = 0; j < n; j++) {
            scanf("%d", &s[j]);
        }
        scanf("%d", &e);
        for(int pass = 0; pass < n - 1; pass++) {
            for(int j = 0; j < n - 1; j++) {
                if(s[j] > s[j+1]) {
                    int hold = s[j+1];
                    s[j+1] = s[j];
                    s[j] = hold;
                }
            }
        }
        for(int j = 0; j < n; j++) {
            total += s[j];
            if(total > e) {
                printf("%s %d %s", "Kaburlah Furina! akan kuhadapi", n - j, "Slime terakhir dengan cara lain!\n");
                break;
            }
        }
        if(total <= e) {
            printf("%s %d %s", "Cih,", n, "slime doang gaakan bisa ngapa ngapain gweh!\n");
        }
    }
}