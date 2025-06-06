#include <stdio.h>

int main() {
    char num[4];
    fgets(num, 4, stdin);
    int power = 1;
    if(num[1] != ' ' || num[1] != '\0') {
        power++;
    } if(num[2] != ' ' || num[2] != '\0') {
        power++;
    }
    int total = 0;
    if(power == 1) {    
        total += num[0] - 48;
    } else if (power == 2) {
        total += (num[0] - 48)*(num[0] - 48);
    } else {
        total += (num[0] - 48)*(num[0] - 48)*(num[0] - 48);
    }
    if(num[1] != ' ' || num[1] != '\0') {
        if(power == 1) {    
            total += num[1] - 48;
        } else if (power == 2) {
            total += (num[1] - 48)*(num[1] - 48);
        } else {
            total += (num[1] - 48)*(num[1] - 48)*(num[1] - 48);
        }
    } if(num[2] != ' ' || num[2] != '\0') {
        if(power == 1) {    
            total += num[2] - 48;
        } else if (power == 2) {
            total += (num[2] - 48)*(num[2] - 48);
        } else {
            total += (num[2] - 48)*(num[2] - 48)*(num[2] - 48);
        }
    }
    int n;
    sscanf(num, "%d", &n);
    if(n == total) {
        printf("Merupakan Bilangan Armstrong\n");
    } else {
        printf("Bukan Merupakan Bilangan Armstrong");
    }
}