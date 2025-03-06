#include <stdio.h>
#include <string.h>
#define MAX_CHAR 1000

int palindrome(char *word);

int main() {
    char word[MAX_CHAR];
    printf("Enter a word or sentence: ");
    fgets(word, MAX_CHAR, stdin);

    if (palindrome(word)) {
        printf("It is a palindrome\n");
    } else {
        printf("It is not a palindrome\n");
    }
    return 0;
}

int palindrome(char *word) {
    int len = strlen(word);
    int left = 0, right = len - 2;
    unsigned int mask = 0;

    for(int i = 0; i < len; i++) {
        if((word[i] >= 65) && (word[i] <= 90)) {
            word[i] += 32;
        }
    }

    while (left < right) {
        mask ^= (1U << (word[left] - 'a'));
        mask ^= (1U << (word[right] - 'a'));
        left++;
        right--;
    }
    return (mask == 0);
}