#include <stdio.h>

int main() {
    int num, len, a ,b ,c;
    scanf("%d", &a);
    if(num < 10) {
        len = 1;
        a = num;
    } else if(num < 100) {
        len = 2;
        a = num % 10;
        b = num % 10*a;
    } else {
        len = 3;
        a = num % 10;
        b = num % 10*a;
        c = num % ((100*b) + (10*a)); 
    }

    


    return 0;
}