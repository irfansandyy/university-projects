#include <stdio.h>
#include <string.h>
#define MAX_STR 1001
#define MAX_N 1000000

int main() {
    int n;
    scanf("%d", &n);
    char outputList[n][(MAX_STR * 2) + 100];
    for(int i = 0; i < n; i++) {
        char cmd[8];
        char strA[MAX_STR];
        char strB[MAX_STR];
        int charfreqA[26] = {0};
        int charfreqB[26] = {0};
        scanf("%s %s %s", cmd, strA, strB);
        int flip_true = 0, anagram_true = 0;
        int flip_results_true = 1, anagram_results_true = 1;

        if(strcmp(cmd, "FLIP") == 0) {
            flip_true = 1;
        } else if(strcmp(cmd, "ANAGRAM") == 0) {
            anagram_true = 1;
        }
        
        if(flip_true == 1) {
            for(long long unsigned l = 0; l < strlen(strA); l++) {
                if(strA[l] == strB[strlen(strB) - l - 1]) {
                    flip_results_true = 1;
                    continue;
                } else {
                    flip_results_true = 0;
                    break;
                }
            }
            if(flip_results_true == 1) {
                sprintf(outputList[i], "%s %s %s %s", "Flip", strA, "to get", strB);
            } else {
                sprintf(outputList[i], "%s", "This cannot lah bro");
            }
        } else if(anagram_true == 1) {
            for(long long unsigned l = 0; l < strlen(strA); l++) {
                for(int m = 0; m < 26; m++) {
                    if(strA[l] == 65 + m || strA[l] == 97 + m) {
                        ++charfreqA[m];
                    }
                }
            }
            for(long long unsigned l = 0; l < strlen(strB); l++) {
                for(int m = 0; m < 26; m++) {
                    if(strB[l] == 65 + m || strB[l] == 97 + m) {
                        ++charfreqB[m];
                    }
                }
            }
            for(int l = 0; l < 26; l++) {
                if(charfreqA[l] == charfreqB[l]) {
                    anagram_results_true = 1;
                    continue;
                } else {
                    anagram_results_true = 0;
                    break;
                }
            }
            if(anagram_results_true == 1) {
                sprintf(outputList[i], "%s %s %s %s", "Hhm", strA, "can be arranged into", strB);
            } else {
                sprintf(outputList[i], "%s", "This cannot lah bro");
            }
        }
    }
    for(int i = 0; i < n; i++) {
        printf("%s", outputList[i]);
        printf("\n");
    }
}