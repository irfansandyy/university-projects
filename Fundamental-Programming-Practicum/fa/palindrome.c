#include <stdio.h>
#include <string.h>

int main() {
    char text[201];
    scanf("%s", text);
    int len = strlen(text);
    int isNotPalindrome = 0;
    for(int i = 0; i < len/2; i++) {
        if(text[i] == text[len - 1 - i]) {
            continue;
        } else {
            isNotPalindrome = 1;
            break;
        }
    }
    if(isNotPalindrome == 1) printf("BUKAN PALINDROM");
    else printf("PALINDROM");
}