#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int perulangan = (n%2==0) ? 5 : 6;
    int condition = 1;
    int factor = 0;
    if(n%2==0) {
        char text[5] = {'G', 'E', 'N', 'A', 'P'};
    } else if(n%2==1) {
        char text[6] = {'G', 'A', 'N', 'J', 'I', 'L'};
    }
    while(n%2==0) {
        for(int i = 0; i < n; i++) {
        }
        if(factor/2 == n) {
            factor--;
            break;
        }
        factor++;
    }
}