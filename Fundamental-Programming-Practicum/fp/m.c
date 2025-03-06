#include <stdio.h>

int main() {
    int Q, K, sapiTerbaik = 0;
    scanf("%d %d", &Q, &K);

    for (int i = 1; i <= Q; i++) {
        sapiTerbaik = (sapiTerbaik + K) % i;
    }
    sapiTerbaik += 1;
    printf("yapp, sapi ke %d sepertinya memang yang terbaik.", sapiTerbaik);

    return 0;
}
