#include <stdio.h>
#include <string.h>

int getPrecedence(char key) {
    switch (key) {
        case 'q': return 1;
        case 'w': return 2;
        case 'e': return 3;
        case 'r': return 4;
        case 't': return 5;
        case 'y': return 6;
        case 'u': return 7;
        case 'i': return 8;
        case 'o': return 9;
        case 'p': return 10;
        case 'a': return 11;
        case 's': return 12;
        case 'd': return 13;
        case 'f': return 14;
        case 'g': return 15;
        case 'h': return 16;
        case 'j': return 17;
        case 'k': return 18;
        case 'l': return 19;
        case 'z': return 20;
        case 'x': return 21;
        case 'c': return 22;
        case 'v': return 23;
        case 'b': return 24;
        case 'n': return 25;
        case 'm': return 26;
    }
}

int main() {
    char text[100002];
    scanf("%s", text);
    char* leftPtr = text + strlen(text)-2;
    char* rightPtr = text + strlen(text)-1;
    while(leftPtr >= text && getPrecedence(*leftPtr) >= getPrecedence(*rightPtr)) {
        rightPtr--;
        leftPtr--;
    }
    if(leftPtr < text) {
        char reversePrecedence[] = "qwertyuiopasdfghjklzxcvbnm";
        for(int i = 0; i < strlen(text); i++) printf("%c", reversePrecedence[i]);
    } else {
        rightPtr = text + strlen(text)-1;
        while(getPrecedence(*leftPtr) >= getPrecedence(*rightPtr)) rightPtr--;
        char temp = *leftPtr;
        *leftPtr = *rightPtr;
        *rightPtr = temp;
        
        rightPtr = text + strlen(text)-1;
        leftPtr += 1;
        while(leftPtr < rightPtr) {
            temp = *leftPtr;
            *leftPtr = *rightPtr;
            *rightPtr = temp;
            leftPtr++;
            rightPtr--;
        }
        for(int i = 0; i < strlen(text); i++) printf("%c", *(text+i));
    }
}