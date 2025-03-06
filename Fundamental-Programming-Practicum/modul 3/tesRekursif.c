#include <stdio.h>
 
int power(int a, int m) {
    int hasil = 1;
    for(int i = 0; i < m; i++) {
        hasil *= a;
    }
    return hasil;
}
 
int main()
{
    printf("%d\n", power(2,3));
    return 0;
}