#include <stdio.h>
#include <string.h>
#define MAX_STRLEN 20

int rank(char authority[]){
    if (!strcmp(authority, "furina")) return 2;
    else if (!strcmp(authority, "hutao")) return 1;
    else if (!strcmp(authority, "lyney")) return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    char prevAuthority[MAX_STRLEN] = " ";
    char prevAction[MAX_STRLEN] = " ";
    char highestAuthority[MAX_STRLEN] = " ";

    char authority[MAX_STRLEN];
    char action[MAX_STRLEN];

    while (n--) {
        scanf("%s %s", authority, action);
        if (!strcmp(prevAction, " ")) {
            if (!strcmp(action, "istirahat")) {
                printf("Oceanid Minion marah karena belum diperintah apa-apa, tetapi sudah disuruh istirahat!\n");
                return 0;
            } else if (!strcmp(action, "beraksi")) {
                strcpy(prevAction, action);
                strcpy(prevAuthority, authority);
                strcpy(highestAuthority, authority);
                printf("Oceanid Minion %s sesuai keinginan %s.\n", action, authority);
            }
        } else {
            if (rank(authority) < rank(highestAuthority)) {
                printf("Oceanid Minion tidak nurut karena wewenang %s lebih rendah dari %s.\n", authority, highestAuthority);
            } else {
                if (!strcmp(action, prevAction)) {
                    printf("Oceanid Minion sudah diperintah %s oleh %s.\n", action, prevAuthority);
                } else {
                    printf("Oceanid Minion %s sesuai keinginan %s.\n", action, authority);
                    strcpy(prevAction, action);
                    strcpy(prevAuthority, authority);
                }
                strcpy(highestAuthority, authority);
            }
        }
    }
}