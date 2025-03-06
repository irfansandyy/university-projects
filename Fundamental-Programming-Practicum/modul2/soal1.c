#include <stdio.h>
#define MAX_ID 10000

int main() {
    int n;
    scanf("%d", &n);

    if(n == 0) {
        printf("%d", -1);
        return 0;
    }

    int id[MAX_ID];
    int freq[11] = {0};
    int modus = 0;
    int seri = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &id[i]);
        if((id[i] < 1 ) && id[i] > 10) {
            printf("%d", -1);
            return 0;
        }
        ++freq[id[i]];
    }
    for(int i = 1; i < 11; i++) {
        if(freq[i] > freq[modus]) {
            modus = i;
        }
    }
    for(int i = 1; i < 11; i++) {
        if(i == modus) {
            continue;
        }
        if((freq[i] == freq[modus])) {
            seri = 1;
        }
    }
    if(seri == 1) {
        printf("%d", -1);
    } else {
        printf("%d", modus);
        printf("\n%d", n - freq[modus]);
    }
    return 0;
}