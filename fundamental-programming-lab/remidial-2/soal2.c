#include <stdio.h>
#include <string.h>
#define MAX_S 1001

int main() {
    char s[MAX_S];
    int freq[27] = {0};
    int modus = 26;
    fgets(s, MAX_S, stdin);
    for(int i = 0; i < strlen(s) - 1; i++) {
        if(s[i] == 32) {
            continue;
        } else {
            freq[s[i] - 97]++;
        }
    }
    for(int i = 0; i < 26; i++) {
        if(freq[i] > freq[modus]) {
            modus = i;
        }
    }
    for(int i = 0; i < 26; i++) {
        if(freq[i] == 0) {
            continue;
        } else {
            printf("%c: %d\n", 97 + i, freq[i]);
        }
    }
    if(modus == 26) {
        printf("hmmm, i don't have anything to show");
    } else {    
        printf("Most frequent character: %c with count: %d", 97 + modus, freq[modus]);
    }
}