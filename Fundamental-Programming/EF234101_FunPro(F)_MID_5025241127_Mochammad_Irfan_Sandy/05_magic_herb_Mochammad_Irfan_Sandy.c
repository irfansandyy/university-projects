#include <stdio.h>

int operations(int i, int j);

int main() {
    int n[15] = {94,222,221,186,181,208,207,110,187,185,17,212,115,215,100};
    for(int i = 14; i > 0; i--) n[i-1] = operations(n[i], n[i-1]);
    for(int i = 0; i < 14; i++) printf("%c\n", n[i]);
    return 0;
}

int operations(int i, int j) {
    int temp;
    temp = j + i;
    if(temp >= 65 && temp <= 122) return temp;
    temp = j - i;
    if(temp >= 65 && temp <= 122) return temp;
    temp = j*2 - i;
    if(temp >= 65 && temp <= 122) return temp;
    temp = (j-3)*2 + i;
    if(temp >= 65 && temp <= 122) return temp;
    return i;
}