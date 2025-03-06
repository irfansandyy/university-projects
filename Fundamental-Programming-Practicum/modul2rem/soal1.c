#include <stdio.h>
#include <string.h>
#define MAX_S 1001

int main() {
    int a;
    char temp;
    char s[MAX_S];
    scanf("%d", &a);
    scanf("%c", &temp);
    fgets(s, MAX_S, stdin);
    for(int i = 0; i < strlen(s) - 1; i++) {
        if(s[i] != 32) {
            if((s[i] + a) > 122) {
                printf("%c", 97 + ((a - (123 - s[i]) % 26)));
            } else if((s[i] + a) < 97) {
                printf("%c", 122 + ((a + (s[i] - 96)) % 26));
            } else {
                printf("%c", s[i] + a);
            }
        } else {
            printf(" ");
        }
    }
}