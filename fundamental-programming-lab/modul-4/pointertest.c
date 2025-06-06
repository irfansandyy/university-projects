#include <stdio.h>
#define llu long long unsigned

int main() {
    int var = 5;
    int* varPtr = &var;
    llu vars = 10u;
    llu* varsPtr = &vars;
    char ch = 20;
    char* chPtr = &ch;
    int**  varPtrPtr = &varPtr;
    printf("%d\n", var);
    printf("%p\n", &var);
    printf("%p\n", varPtr);
    printf("%p\n", &varPtr);
    printf("%d\n", *varPtr);
    printf("%llu\n", vars);
    printf("%p\n", &vars);
    printf("%p\n", varsPtr);
    printf("%p\n", &varsPtr);
    printf("%llu\n", *varsPtr);
    printf("%c\n", ch);
    printf("%p\n", &ch);
    printf("%p\n", chPtr);
    printf("%p\n", &chPtr);
    printf("%c\n", *chPtr);
    printf("\n%d", **varPtrPtr);
}