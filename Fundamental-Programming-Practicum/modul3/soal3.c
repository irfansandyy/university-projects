#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isStrong=true;

bool CheckNumber(char password[]) {
    bool thereIsNumber = false;
    for(int i = 0; i < (int) strlen(password); i++) {
        if((password[i] >= '0') && (password[i] <= '9')) {
            thereIsNumber = true;
        }
    }
    if(isStrong) isStrong = thereIsNumber;
    return thereIsNumber;
}

bool CheckUppercase(char password[]) {
    bool thereIsUppercase = false;
    for(int i = 0; i < (int) strlen(password); i++) {
        if((password[i] >= 'A') && (password[i] <= 'Z')) {
            thereIsUppercase = true;
        }
    }
    if(isStrong) isStrong = thereIsUppercase;
    return thereIsUppercase;
}

bool CheckKey(char password[], int key) {
    int sum = 0;
    for(int i = 0; i < (int) strlen(password); i++) {
        if((password[i] >= '0') && (password[i] <= '9')) {
            sum += password[i] - '0';
        }
    }
    if(isStrong) isStrong = (sum == key);
    return (sum == key);
}

int main(){
    char password[128];
    int key;
    scanf("%s %d",password, &key);
    if(!CheckNumber(password))printf("Password needs number\n");
    if(!CheckUppercase(password))printf("Password requires at least one uppercase letter\n");
    if(!CheckKey(password, key))printf("Digits in password not equal to key\n");
    if(isStrong)printf("Password is strong, just like you\n");
    else printf("Weak password, fix your mistakes\n");
}